#include "struct.hpp"
int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    long long n;
    TDynVector dynVector(10000000);
    if(std::cin >> n){
        dynVector.Print(n);
    }
    std::cout << "\n";
    return 0;
}
