import random
import sys
import string


def generate_random_string(length):
    letters = string.ascii_lowercase
    rand_string = ''.join(random.choice(letters) for i in range(length))
    return rand_string


if __name__ == "__main__":
    count_of_tests = int(sys.argv[1]) + 1
    for enum in range(1, count_of_tests):
        keys = dict()
        test_file_name = "tests/{:02d}".format(enum)
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:

            num_of_req = 10 ** enum
            req = generate_random_string(num_of_req)
            output_file.write("{0}".format(req))
            req = req + req
            minIndex = 0
            for i in range(1, num_of_req):
                for j in range(num_of_req):
                    if req[i+j] < req[minIndex+j]:
                        minIndex = i
                        break
                    elif req[i+j] > req[minIndex+j]:
                        break
            ans = req[minIndex:minIndex+num_of_req]
            answer_file.write("{0}\n".format(ans))
