#include "vector.hpp"
#include <cstdio>
#include <iostream>


void CountingSort(NMystd::TVector<NMystd::TItem> &data) {
    for (int i = 0; i < 32; ++i){
        NMystd::TVector<NMystd::TVector<NMystd::TItem>> buf(16, NMystd::TVector<NMystd::TItem>());
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

int main() {
	NMystd::TVector<NMystd::TItem> a;
	NMystd::TItem cur;
	std::cin.tie(0); 
	std::cout.tie(0); 
	std::ios_base::sync_with_stdio(0);
	while (std::cin >> cur.key >> cur.value) {
		a.Push_back(cur);
	}
	CountingSort(a);
	for (int i = 0; i < a.Size(); i++) {
		std::cout << a[i].key << ' ' << a[i].value << '\n';
	}
	return 0;
}