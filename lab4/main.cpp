#include <cstring>
#include "kmp.hpp"
int main(){
    bool flagPatternText = true;
    long long stringId = 1, wordId = 1;
    std::vector<NSearch::TWord> pattern;
    std::vector<NSearch::TWord> text;
    char c;
    long long wordIndex = 0;
    char *word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
    while ((c = (char)getchar()) > 0){
        if(c != '\n' && c != ' '){
            c = (char)tolower(c);
            word[wordIndex] = c;
            ++wordIndex;
        }
        else if(c == '\n'){
            NSearch::TWord cur;
            cur.WordSize = wordIndex;
            cur.Word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
            if(flagPatternText){
                pattern.push_back(cur);
                std::memcpy(cur.Word, word, sizeof(char) * MAX_WORD_SIZE);
                NSearch::Clear(word, MAX_WORD_SIZE);
                flagPatternText = false;
            }
            else{
                cur.StringId = stringId;
                cur.WordId = wordId;
                std::memcpy(cur.Word, word, sizeof(char)*MAX_WORD_SIZE);
                text.push_back(cur);
                wordId = 1;
                ++stringId;
                NSearch::Clear(word, MAX_WORD_SIZE);
            }
            wordIndex = 0;
        }
        else if(c == ' '){
            NSearch::TWord cur;
            cur.Word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
            cur.WordSize = wordIndex;
            if(flagPatternText){
                std::memcpy(cur.Word, word, sizeof(char)*MAX_WORD_SIZE);
                pattern.push_back(cur);
            }
            else{
                cur.WordId = wordId;
                cur.StringId = stringId;
                std::memcpy(cur.Word, word, sizeof(char)*MAX_WORD_SIZE);
                text.push_back(cur);
                ++wordId;
            }
            wordIndex = 0;
            NSearch::Clear(word, MAX_WORD_SIZE);
        }
    }
    std::vector<long long> ans = KMP(pattern, text);
    long long patternSize = pattern.size();
    for(long long i = 0; i < patternSize; ++i){
        free(pattern[i].Word);
    }
    long long textSize = text.size();
    for(long long i = 0; i < textSize; ++i){
        free(text[i].Word);
    }
    for (const long long & id : ans) {
        printf("%lld, %lld\n", text[id].StringId, text[id].WordId);
    }
    free(word);
    return 0;
}

