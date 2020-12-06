//
// Created by nikita on 05.12.2020.
//

#ifndef LAB4_KMP_HPP
#define LAB4_KMP_HPP
#include <string>
#include <vector>
int MAX_WORD_SIZE = 17;
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
            int currInd = res[i - 1];
            while(currInd > 0 && input[i] != input[currInd]){
               currInd = res[currInd - 1];
            }
            if (input[i] == input[currInd]){
                ++currInd;
            }
            res[i] = currInd;
        }
        return res;
    }
    std::vector<int> KMP(std::vector<TWord>&pattern, std::vector<TWord> &text){
        int patternSize = pattern.size();
        int textSize = text.size();
        std::vector<TWord> resText(patternSize + textSize + 1);
        for(int i = 0; i < patternSize; ++i){
            resText[i] = pattern[i];
        }
        resText[patternSize].Word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
        resText[patternSize].Word[0] = '#';
        for(int i = 0; i < textSize; ++i){
            resText[patternSize + i + 1] = text[i];
        }
        std::vector<int> prefix = PrefixFunction(resText);
        std::vector<int> answer;
        if (patternSize > textSize){
            return answer;
        }
        for(int i = 0; i < textSize; ++i){
            if(prefix[patternSize + i + 1] == patternSize){
                answer.push_back(i - patternSize + 1);
            }
        }
        return answer;
    }
}
#endif //LAB4_KMP_HPP
