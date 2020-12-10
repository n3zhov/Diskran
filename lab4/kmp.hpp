//
// Created by nikita on 05.12.2020.
//

#ifndef LAB4_KMP_HPP
#define LAB4_KMP_HPP
#include <vector>
#include <string>
namespace NSearch {
    struct TWord{
        std::string Word;
        long long WordId, StringId;
    };
    std::string tolower(std::string &data){
        int size = data.size();
        for (int i = 0; i < size; ++i){
            data[i] = std::tolower(data[i]);
        }
        return data;
    }
    std::vector<long long> PrefixFunction(const std::vector<TWord> &input) {
        std::vector<long long> res(input.size());
        long long length = input.size();
        for (long long i = 1; i < length; ++i) {
            long long j = res[i - 1];
            while(j > 0 && input[i].Word != input[j].Word){
               j = res[j - 1];
            }
            if (input[i].Word == input[j].Word){
                ++j;
            }
            res[i] = j;
        }
        return res;
    }
    std::vector<long long> KMP(std::vector<TWord>&pattern, std::vector<TWord> &text, std::vector<long long> &prefix){
        long long patternSize = pattern.size();
        long long textSize = text.size();
        long long i = 0;
        std::vector<long long> answer;
        if (patternSize > textSize || patternSize == 0) {
            return answer;
        }
        while (i < textSize - patternSize + 1) {
            long long j = 0;
            while (j < patternSize && pattern[j].Word == text[i + j].Word) {
                ++j;
            }
            if (j == patternSize) {
                answer.push_back(i);
            }
            else{
                if (j > 0 && j > prefix[j - 1]) {
                    i = i + j - prefix[j - 1];
                    continue;
                }
            }
            ++i;
        }
        return answer;
    }
}
#endif //LAB4_KMP_HPP
