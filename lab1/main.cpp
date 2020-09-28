#include "vector.hpp"
#include <cstdio>
#include <iostream>


void CountingSort(NMystd::TVector<NMystd::TItem> &data) {
    for (int i = 0; i < 32; ++i){
        NMystd::TVector<NMystd::TVector<NMystd::TItem> > buf(16, NMystd::TVector<NMystd::TItem>());
        for (int m = 0; m < data.Size(); ++m){
            char c = data[m].key[31-i];
            if(c == 'a'){
                buf[10].PushBack(data[m]);
            }
            else if(c == 'b'){
                buf[11].PushBack(data[m]);
            }
            else if(c == 'c'){
                buf[12].PushBack(data[m]);
            }
            else if(c == 'd'){
                buf[13].PushBack(data[m]);
            }
            else if(c == 'e'){
                buf[14].PushBack(data[m]);
            }
            else if(c == 'f'){
                buf[15].PushBack(data[m]);
            }
            else{
                int index = (int)c - '0';
                buf[index].PushBack(data[m]);
            }
        }
        data.Clear();
        for (int m = 0; m < 16; ++m){
        	for (int j = 0; j < buf[m].Size(); ++j){
                data.PushBack(buf[m][j]);
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
		a.PushBack(cur);
	}
	CountingSort(a);
	for (int i = 0; i < a.Size(); i++) {
		std::cout << a[i].key << ' ' << a[i].value << '\n';
	}
	return 0;
}