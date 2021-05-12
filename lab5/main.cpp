#include <iostream>
#include "suffTree.hpp"
int main(){
    ios::sync_with_stdio(0);
    cout.tie(0), cin.tie(0);
    string text;
    cin >> text;
    int n = text.size();
    text = text+text;
    TSuffixTree suffixTree(text);
    std::string res = suffixTree.Linearization(n);
    std::cout << res << "\n";
    return 0;
}
