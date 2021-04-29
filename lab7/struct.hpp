#include <string>
#include <iostream>
#include <vector>

struct TNumber{
    long long cost;
    std::string *operation;
    TNumber(){
        cost = 0;
    }
};

bool operator <(TNumber &lhs, TNumber &rhs){
    return lhs.cost < rhs.cost;
}

std::ostream &operator << (std::ostream &of, TNumber &number){
    of << *number.operation;
    return of;
}

class TDynVector{
private:
    std::string empty;
    std::string fType = "-1 ";
    std::string sType = "/2 ";
    std::string tType = "/3 ";
    TNumber *Data;
    long long Size = 0;
    void CountCost(){
        Data[1].operation = &empty;
        long long currIndex = 2;
        std::string *operation = &empty;
        while(currIndex != Size + 1){
            long long minCost = -1;
            if(currIndex % 3 == 0){
                minCost = Data[currIndex/3].cost;
                operation = &tType;
            }
            if(currIndex % 2 == 0 && (Data[currIndex/2].cost < minCost || minCost == -1)){
                minCost = Data[currIndex / 2].cost;
                operation = &sType;
            }
            if (currIndex - 1 > 0 && (Data[currIndex-1].cost < minCost || minCost == -1)){
                minCost = Data[currIndex - 1].cost;
                operation = &fType;
            }
            Data[currIndex].cost = minCost + currIndex;
            Data[currIndex].operation = operation;
            ++currIndex;
        }
    }
public:
    TDynVector() = default;
    TDynVector(long long size){
        Data = new TNumber[size + 1];
        this->Size = size;
        this->CountCost();
    }
    void Print(long long n){
        std::cout << this->Data[n].cost << "\n";
        PrintHelper(n);
    }
    void PrintHelper(long long n){
        std::cout << this->Data[n];
        if(n != 1) {
            if (this->Data[n].operation == &tType) {
                PrintHelper(n / 3);
            } else if (this->Data[n].operation == &sType) {
                PrintHelper(n / 2);
            } else if (this->Data[n].operation == &fType) {
                PrintHelper(n - 1);
            }
        }
    }
    TNumber& operator[](const long long index){
        return Data[index];
    }
    ~TDynVector(){
        delete [] Data;
    }
};

