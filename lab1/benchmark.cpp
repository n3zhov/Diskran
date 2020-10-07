
#include "vector.hpp"

#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>

const int KEY_BIT_SIZE = 4;
const int VALUE_SIZE = 2049;
const unsigned int MAX_KEY = 0xffff;
const int STR_KEY_SIZE = 33;
const int HEX_PRECISION = 4;
const char ZERO_CHAR = '0';
const int ZERO = 0;
const int ONE = 1;
const int HEX_MULTIPLY = 16;
const char A_CHAR = 'a';
const char F_CHAR = 'f';
const char NINE_CHAR = '9';

bool compare(NMyStd::TItem const& lhs, NMyStd::TItem const& rhs){
    for (int i = 0; i < KEY_SIZE; ++i){
        if(lhs.Key[i] < rhs.Key[i]){
            return true;
        }
        else if(lhs.Key[i] > rhs.Key[i]){
            return false;
        }
    }
    return false;
}

void CountingSort(NMyStd::TVector<NMyStd::TItem> &data, int bit) {
    NMyStd::TVector<long long> countArray(MAX_KEY + ONE, ZERO);
    long long size = data.Size();
    for (unsigned int i = 0; i <= MAX_KEY; ++i){
        countArray[i] = ZERO;
    }
    for (long long i = 0; i < size; ++i){
        countArray[data[i].Key[bit]] += ONE;
    }
    for (unsigned int i = 1; i <= MAX_KEY; ++i){
        countArray[i] += countArray[i - ONE];
    }
    NMyStd::TItem *result = new NMyStd::TItem[size];
    for (long long i = size - ONE; i >= 0; --i){
        result[countArray[data[i].Key[bit]] - ONE] = data[i];
        --countArray[data[i].Key[bit]];
    }
    for (long long i = 0; i < size; ++i){
        data[i] = result[i];
    }
    delete [] result;
}

void BitwiseSort(NMyStd::TVector<NMyStd::TItem> &data){
    for (int i = KEY_SIZE - ONE; i >= 0; --i){
        CountingSort(data, i);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    NMyStd::TVector<NMyStd::TItem> data;
    std::vector<NMyStd::TItem> benchmarkData;

    char strKey [STR_KEY_SIZE];
    NMyStd::TItem cur;
    cur.Value = nullptr;

    char bufInput [VALUE_SIZE];
    NMyStd::TVector<char*> valueData;
    auto start = std::chrono::steady_clock::now();
    while (std::cin >> strKey >> bufInput) {
        for (int & i : cur.Key){
            i = ZERO;
        }
        for (int i = KEY_SIZE - ONE; i >= 0; --i){
            int hexMultiply = ONE;
            for (int j = KEY_BIT_SIZE - ONE; j >= 0; --j){
                if (strKey[i * KEY_BIT_SIZE + j] >= ZERO_CHAR && strKey[i * KEY_BIT_SIZE + j] <= NINE_CHAR){
                    cur.Key[i] += (strKey[i * KEY_BIT_SIZE + j] - ZERO_CHAR) * hexMultiply;
                }
                else if (strKey[i * KEY_BIT_SIZE + j] >= A_CHAR && strKey[i * KEY_BIT_SIZE + j] <= F_CHAR){
                    cur.Key[i] += (strKey[i * KEY_BIT_SIZE + j] - A_CHAR + 10) * hexMultiply;
                }
                hexMultiply *= HEX_MULTIPLY;
            }
        }
        char *curValue = new char[VALUE_SIZE];
        std::memcpy(curValue, bufInput, sizeof(char)*VALUE_SIZE);
        data.PushBack(cur);
        benchmarkData.push_back(cur);
        valueData.PushBack(curValue);
    }
    for (int i = 0; i < valueData.Size(); ++i){
        data[i].Value = &valueData[i];
        benchmarkData[i].Value = &valueData[i];
    }
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cerr << "input time " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
    
    start = std::chrono::steady_clock::now();
    BitwiseSort(data);
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "custom bitwise sort " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    sort(benchmarkData.begin(), benchmarkData.end(), compare);
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "stable sort from std " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < data.Size(); ++i) {
        for (int j = 0; j < KEY_SIZE; ++j){
            std::cout << std::hex << std::setw(HEX_PRECISION) << std::setfill(ZERO_CHAR) << benchmarkData[i].Key[j];
        }
        std::cout << " " << *benchmarkData[i].Value << "\n";
    }
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "output time " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
    
    for (int i = 0; i < valueData.Size(); ++i){
        delete[] valueData[i];
    }
    return 0;
}
