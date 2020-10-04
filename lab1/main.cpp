#include "vector.hpp"
#include <cstdio>
const int MAX_KEY = 16;
void CountingSort(NMyStd::TVector<NMyStd::TItem> &data, int bit) {
    NMyStd::TVector<int> count(MAX_KEY, 0);
    int size = (int)data.Size();
    for (int i = 0; i < size; ++i) {
        char c = data[i].key[31-bit];
        int bitValue;
        int digitSummand = 10;
        if (c >= 'a' && c <= 'z') {
            bitValue = digitSummand + c - 'a';
        }
        else{
            bitValue = c - '0';
        }
        count[bitValue]++;
    }

    for (int i = 1; i < MAX_KEY; ++i) {
        count[i] = count[i] + count[i - 1];
    }

    NMyStd::TVector<NMyStd::TItem> res(data.Size());
    for (int i = size - 1; i >= 0; --i) {
        char c = data[i].key[31-bit];
        int bitValue;
        int digitSummand = 10;
        if (c >= 'a' && c <= 'z') {
            bitValue = digitSummand + c - 'a';
        }
        else{
            bitValue = c - '0';
        }
        res[count[bitValue] - 1] =  data[i];
        count[bitValue]--;
    }
    for (int i = 0; i < size; ++i) {
        data[i] = res[i];
    }
}

void BitwiseSort(NMyStd::TVector<NMyStd::TItem> &data){
    for (int i = 0; i < 32; ++i){
        CountingSort(data, i);
    }
}

int main() {
    NMyStd::TVector<NMyStd::TItem> a;
    NMyStd::TItem cur;
    char *bufInput = new char[2049];
    NMyStd::TVector<char*> ValueData;
    while (scanf("%s%s", cur.key, bufInput) > 0) {
        a.PushBack(cur);
        ValueData.PushBack(bufInput);
    }
    for (int i = 0; i < ValueData.Size(); ++i){
        a[i].value = &(ValueData[i]);
    }
    BitwiseSort(a);
    for (int i = 0; i < a.Size(); i++) {
        printf("%s %s\n", a[i].key, *a[i].value);
    }
    delete [] bufInput;
    return 0;
}
