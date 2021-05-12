//
// Created by nezhov on 12.05.2021.
//
#include <string>
#include <iostream>
#include <chrono>
#include "suffTree.hpp"
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cout.tie(0), cin.tie(0);
    int min;
    string text;
    cin >> text;
    int n = text.size();
    text = text+text;
    min = 0;
    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i < n; i++){
        for(int j = 0; j < n; j++){
            if(text[i+j] < text[min+j]){
                min = i;
                break;
            }
            else if (text[i+j] > text[min+j]){
                break;
            }
        }
    }
    string ans = text.substr(min, n);
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cerr << "naive linearization " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
    start = std::chrono::steady_clock::now();
    TSuffixTree suffixTree(text);
    std::string res = suffixTree.Linearization(n);
    std::cout << ans << "\n";
    finish = std::chrono::steady_clock::now();
    dur = finish - start;
    std::cerr << "suffTree linearization " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
}
