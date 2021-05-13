#include "struct.hpp"
#include <chrono>
using namespace std;
long long minCost(long long n){
    long long f, s, t;
    if(n == 1){
        return 0;
    }
    if(n%3==0){
        t = minCost(n/3);
    }
    else{
        t = 1e8;
    }
    if(n%2==0){
        s = minCost(n/2);
    }
    else{
        s = 1e8;
    }
    f = minCost(n-1);
    return min(f, min(s, t)) + n;
}
int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    long long n;
    auto start = std::chrono::steady_clock::now();
    TDynVector dynVector(10000000);
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    if(std::cin >> n){
        start = std::chrono::steady_clock::now();
        dynVector.Print(n);
        finish = std::chrono::steady_clock::now();
    }
    dur += (finish - start);
    std::cerr << "Dynamic programming solution time " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
    << " ms" << std::endl;
    start = std::chrono::steady_clock::now();
    long long ans = minCost(n);
    std::cout << ans << endl;
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "Naive algorithm solution time " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
              << " ms" << std::endl;
    std::cout << "\n";
    return 0;
}
