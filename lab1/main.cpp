#include "vector.hpp"
#include <iostream>
#include <iomanip>


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

void CountingSort(NMyStd::TVector<NMyStd::TItem> &data, int bit) {
    NMyStd::TVector<long long> countArray(MAX_KEY + ONE, ZERO);
    long long size = data.Size();
    for (long long i = 0; i < size; ++i) {
        ++countArray[data[i].Key[bit]];
    }
    for (unsigned int i = 1; i <= MAX_KEY; ++i) {
        countArray[i] += countArray[i - ONE];
    }
    NMyStd::TItem *result = new NMyStd::TItem[size];
    for (long long i = size - ONE; i >= 0; --i) {
        result[countArray[data[i].Key[bit]] - ONE] = data[i];
        --countArray[data[i].Key[bit]];
    }
    for (long long i = 0; i < size; ++i) {
        data[i] = result[i];
    }
    delete [] result;
}

void BitwiseSort(NMyStd::TVector<NMyStd::TItem> &data) {
    for (int i = KEY_SIZE - ONE; i >= 0; --i) {
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
    NMyStd::TVector<char*> valueData;

    while (std::cin >> strKey >> bufInput) {
        for (int & i : cur.Key) {
            i = ZERO;
        }
        for (int i = KEY_SIZE - ONE; i >= 0; --i) {
            int hexMultiply = ONE;
            for (int j = KEY_BIT_SIZE - ONE; j >= 0; --j) {
                if (strKey[i * KEY_BIT_SIZE + j] >= ZERO_CHAR && strKey[i * KEY_BIT_SIZE + j] <= NINE_CHAR) {
                    cur.Key[i] += (strKey[i * KEY_BIT_SIZE + j] - ZERO_CHAR) * hexMultiply;
                }
                else if (strKey[i * KEY_BIT_SIZE + j] >= A_CHAR && strKey[i * KEY_BIT_SIZE + j] <= F_CHAR) {
                    cur.Key[i] += (strKey[i * KEY_BIT_SIZE + j] - A_CHAR + 10) * hexMultiply;
                }
                hexMultiply *= HEX_MULTIPLY;
            }
        }
        char *curValue = new char[VALUE_SIZE];
        std::memcpy(curValue, bufInput, sizeof(char)*VALUE_SIZE);
        data.PushBack(cur);
        valueData.PushBack(curValue);
    }
    for (int i = 0; i < valueData.Size(); ++i) {
        data[i].Value = &valueData[i];
    }
    BitwiseSort(data);
    for (int i = 0; i < data.Size(); ++i) {
        for (int j = 0; j < KEY_SIZE; ++j) {
            std::cout << std::hex << std::setw(HEX_PRECISION) << std::setfill(ZERO_CHAR) << data[i].Key[j];
        }
        std::cout << " " << *data[i].Value << "\n";
    }
    for (int i = 0; i < valueData.Size(); ++i) {
        delete[] valueData[i];
    }
    return 0;
}