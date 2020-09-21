//
// Created by nikita on 20.09.2020.
//

#include "sort.hpp"
#include "vector.hpp"

namespace mystd{
    void Counting_sort(vector<item> &data) {
        for (int i = 0; i < 32; ++i){
            vector<vector<item>> buf(16, vector<item>());
            for (int m = 0; m < data.Size(); ++m){
                char c = data[m].key[31-i];
                if(c == 'a'){
                    buf[10].Push_back(data[m]);
                }
                else if(c == 'b'){
                    buf[11].Push_back(data[m]);
                }
                else if(c == 'c'){
                    buf[12].Push_back(data[m]);
                }
                else if(c == 'd'){
                    buf[13].Push_back(data[m]);
                }
                else if(c == 'e'){
                    buf[14].Push_back(data[m]);
                }
                else if(c == 'f'){
                    buf[15].Push_back(data[m]);
                }
                else{
                    int index = (int)c - '0';
                    buf[index].Push_back(data[m]);
                }
            }
            data.Clear();
            for (int m = 0; m < 16; ++m){
                for (int j = 0; j < buf[m].Size(); ++j){
                    data.Push_back(buf[m][j]);
                }
            }
        }
    }
}