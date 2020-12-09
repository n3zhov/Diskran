//
// Created by nikita on 05.12.2020.
//

#ifndef LAB4_KMP_HPP
#define LAB4_KMP_HPP
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
const long long MAX_WORD_SIZE = 17;
namespace NSearch {
    struct TWord{
        char *Word;
        long long WordId, StringId, WordSize;
        TWord(){
            Word = nullptr;
            WordId = 0;
            StringId = 0;
            WordSize = 0;
        }
    };
    void Clear(char* string, long long size){
        for (long long i = 0; i < size; ++i){
            string[i] = '\0';
        }
    }
    bool operator == (const TWord& lhs, const TWord &rhs){
        if(lhs.WordSize != rhs.WordSize){
            return false;
        }
        for (long long i = 0; i < lhs.WordSize; ++i){
            if(lhs.Word[i] != rhs.Word[i])
                return false;
        }
        return true;
    }
    bool operator != (const TWord& lhs, const TWord &rhs){
        return !(lhs == rhs);
    }
    void Clear(char *arr) {
        for (long long i = 0; i < MAX_WORD_SIZE; ++i) {
            arr[i] = 0;
        }
    }
    std::vector<long long> PrefixFunction(const std::vector<TWord> &input) {
        std::vector<long long> res(input.size());
        long long length = input.size();
        for (long long i = 1; i < length; ++i) {
            long long j = res[i - 1];
            while(j > 0 && input[i] != input[j]){
               j = res[j - 1];
            }
            if (input[i] == input[j]){
                ++j;
            }
            res[i] = j;
        }
        return res;
    }
    std::vector<long long> KMP(std::vector<TWord>&pattern, std::vector<TWord> &text){
        std::vector<long long> prefix = PrefixFunction(pattern);
        long long patternSize = pattern.size();
        long long textSize = text.size();
        long long i = 0;
        std::vector<long long> answer;
        if (patternSize > textSize || patternSize == 0) {
            return answer;
        }
        while (i < textSize - patternSize + 1) {
            long long j = 0;
            while (j < patternSize && pattern[j] == text[i + j]) {
                ++j;
            }
            if (j == patternSize) {
                answer.push_back(i);
            } else {
                if (j > 0 && j > prefix[j - 1]) {
                    i = i + j - prefix[j - 1] - 1;
                }
            }
            ++i;
        }
        return answer;
    }
}
#endif //LAB4_KMP_HPP
