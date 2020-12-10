#include <iostream>
#include "kmp.hpp"
int main(){
    bool flagPattern = true;
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::vector<NSearch::TWord> pattern;
    std::vector<NSearch::TWord> text;
    NSearch::TWord input;
    std::string word;
    char c = getchar();
    while (c > 0) {
        if (c == '\n') {
            if (!input.Word.empty()) {
                text.push_back(input);
                input.Word.clear();
            }
            ++input.StringId;
            if (flagPattern) {
                std::swap(pattern, text);
                flagPattern = false;
                input.StringId = 1;
            }
            input.WordId = 1;
        } else if (c == '\t' || c == ' ') {
            if (!input.Word.empty()) {
                text.push_back(input);
                input.Word.clear();
                ++input.WordId;
            }
        } else {
            if ('A' <= c and c <= 'Z') {
                c = c + 'a' - 'A';
            }
            input.Word += c;
        }
        c = getchar();
    }
    if (!input.Word.empty()) {
        text.push_back(input);
    }
    std::vector<long long> prefix = NSearch::PrefixFunction(pattern);
    std::vector<long long> ans = KMP(pattern, text, prefix);
    for (long long & id : ans) {
        std::cout << text[id].StringId << ", " << text[id].WordId << '\n';
    }
    return 0;
}
