#! /usr/bin/env bash

set -o errexit
set -o pipefail
set -o nounset

function log_info()
{
  log_ "info" "$@"
}

function log_()
{
  local type=$1
  local message=$2
  local date_str=; date_str=$(date +'%Y-%m-%d %H:%M:%S')
  echo "[${type}] [${date_str}] ${message}"
}

function main() {
  local bin=solution
  test_generate_flag=$1
  log_info "Stage #1 Compiling..."
  if ! (make clean && make) ; then
    echo "ERROR: Failed to compile file."
    exit 1
  fi

  log_info "Stage #2 Test generating..."
  local test_dir=tests
  # shellcheck disable=SC2004
  if (($test_generate_flag == 1)) ; then
    rm -rf ${test_dir}
    mkdir -p ${test_dir}
    if ! (python3 generator.py) ; then
      echo "ERROR: Failed to python generate tests."
      exit 1
    fi
  else
    echo "Skip test generating"
  fi

  log_info "Stage #3 Checking..."
  # shellcheck disable=SC2045
  for test_file in $(ls ${test_dir}/*.t); do
    echo "Execute ${test_file}"
    local tmp_output=${test_dir}/tmp
    if ! ./${bin} < ${test_file} > ${tmp_output} ; then
      echo "ERROR"
      continue
    fi
    answer_file="${test_file%.*}"

    if ! diff -u "${answer_file}.a" ${tmp_output} ; then
      echo "Failed ${test_file}"
    else
      echo "Test ${test_file} OK"
    fi
  done

  rm ${tmp_output}

  log_info "Stage #4 Benchmarking..."
  if ! make benchmark; then
    log_info "Failed to compile benchmark."
    return 1
  fi
  local benchmark_bin=./benchmark
  # shellcheck disable=SC2045
  for test_file in $( ls ${test_dir}/*.t ) ; do
    count_of_lines=$(wc -l < ${test_file})
    log_info "Running ${test_file}" 
    echo "Count of requests is ${count_of_lines}"
    if ! ${benchmark_bin} < ${test_file}; then
      log_error "Failed to run ${benchmark_bin} for ${test_file}."
      return 1
    fi
  done

  make clean
}

# shellcheck disable=SC2068
main $@