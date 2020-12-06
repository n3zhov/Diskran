//
// Created by nikita on 05.12.2020.
//

#ifndef LAB4_KMP_HPP
#define LAB4_KMP_HPP
#include <string>
#include <vector>
const int MAX_WORD_SIZE = 17;
namespace NSearch {
    struct TWord{
        char *Word;
        int WordId, StringId, WordSize;
    };
    void Clear(char* string, int size){
        for (int i = 0; i < size; ++i){
            string[i] = '\0';
        }
    }
    bool operator == (const TWord& lhs, const TWord rhs){
        if(lhs.WordSize != rhs.WordSize){
            return false;
        }
        for (int i = 0; i < lhs.WordSize; ++i){
            if(lhs.Word[i] != rhs.Word[i])
                return false;
        }
        return true;
    }
    bool operator != (const TWord& lhs, const TWord rhs){
        return !(lhs == rhs);
    }
    void Clear(char *arr) {
        for (int i = 0; i < MAX_WORD_SIZE; ++i) {
            arr[i] = 0;
        }
    }
    std::vector<int> PrefixFunction(const std::vector<TWord> &input) {
        std::vector<int> res(input.size());
        res[0] = 0;
        int length = input.size();
        for (int i = 1; i < length; ++i) {
            int j = res[i - 1];
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
    std::vector<int> KMP(std::vector<TWord>&pattern, std::vector<TWord> &text){
        std::vector<int> prefix = PrefixFunction(pattern);
        int patternSize = pattern.size();
        int textSize = text.size();
        int i = 0;
        std::vector<int> answer;
        if (patternSize > textSize) {
            return answer;
        }
        while (i < textSize - patternSize + 1) {
            int j = 0;
            while (j < patternSize and pattern[j] == text[i + j]) {
                ++j;
            }
            if (j == patternSize) {
                answer.push_back(i);
            } else {
                if (j > 0 and j > prefix[j - 1]) {
                    i = i + j - prefix[j - 1] - 1;
                }
            }
            ++i;
        }
        return answer;
    }
}
#endif //LAB4_KMP_HPP
