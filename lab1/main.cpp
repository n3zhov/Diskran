#include "vector.hpp"
#include <cstdio>
#include <iostream>
#include <iomanip>

const unsigned int KEY_BIT_SIZE = 4;
const unsigned int VALUE_SIZE = 2049;
const unsigned int MAX_KEY = 0xffff;
const unsigned int STR_KEY_SIZE = 33;

void CountingSort(NMyStd::TVector<NMyStd::TItem> &data, int bit) {
    NMyStd::TVector<long long> countArray(MAX_KEY + 1, 0);
    long long size = data.Size();
    for (unsigned int i = 0; i <= MAX_KEY; ++i){
        countArray[i] = 0;
    }
    for (long long i = 0; i < size; ++i){
        countArray[data[i].Key[bit]] += 1;
    }
    for (unsigned int i = 1; i <= MAX_KEY; ++i){
        countArray[i] += countArray[i - 1];
    }
    NMyStd::TItem *result = new NMyStd::TItem[size];
    for (long long i = size - 1; i >= 0; --i){
        result[countArray[data[i].Key[bit]] - 1] = data[i];
        --countArray[data[i].Key[bit]];
    }
    for (int i = 0; i < size; ++i){
        std::cout << *result[i].Value << ' ';
    }
    for (long long i = 0; i < size; ++i){
        for (int j = 0; j < KEY_SIZE; ++j){
            data[i].Key[j] = result[i].Key[j];
        }
        data[i].Value = result[i].Value;
    }
}

void BitwiseSort(NMyStd::TVector<NMyStd::TItem> &data){
    for (int i = KEY_SIZE - 1; i >= 0; --i){
        CountingSort(data, i);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    NMyStd::TVector<NMyStd::TItem> data;
    char strKey [STR_KEY_SIZE];
    NMyStd::TItem cur;
    cur.Value = nullptr;
    char bufInput [VALUE_SIZE];
    NMyStd::TVector<char*> ValueData;
    while (std::cin >> strKey >> bufInput) {
        for (int & i : cur.Key){
            i = 0;
        }
        for (int i = KEY_SIZE - 1; i >= 0; --i){
            int hexMultiply = 1;
            for (int j = KEY_BIT_SIZE - 1; j >= 0; --j){
                if (strKey[i * KEY_BIT_SIZE + j] >= '0' && strKey[i * KEY_BIT_SIZE + j] <= '9'){
                    cur.Key[i] += (strKey[i * KEY_BIT_SIZE + j] - '0') * hexMultiply;
                }
                else if (strKey[i * KEY_BIT_SIZE + j] >= 'a' && strKey[i * KEY_BIT_SIZE + j] <= 'f'){
                    cur.Key[i] += (strKey[i * KEY_BIT_SIZE + j] - 'a' + 10) * hexMultiply;
                }
                hexMultiply *= 16;
            }
        }
        char *curValue = new char[VALUE_SIZE];
        std::memcpy(curValue, bufInput, sizeof(char)*VALUE_SIZE);
        data.PushBack(cur);
        ValueData.PushBack(curValue);
    }
    for (int i = 0; i < ValueData.Size(); ++i){
        data[i].Value = &ValueData[i];
    }
    BitwiseSort(data);
    for (int i = 0; i < data.Size(); ++i) {
        for (int j = 0; j < KEY_SIZE; ++j){
            std::cout << std::hex << std::setw(4) << std::setfill('0') << data[i].Key[j];
        }
        std::cout << " " << *data[i].Value << "\n";
    }
    return 0;
}
