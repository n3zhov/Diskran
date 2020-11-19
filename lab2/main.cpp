#include <iostream>
#include <cstring>
#include <cctype>
#include "item.hpp"
#include "tree.hpp"

int main(){
    char readStr[MAX_LEN+1];
    NMyStd::TRBTree* rbTree = new NMyStd::TRBTree;
    while(scanf("%s", readStr) > 0){
        if (strcmp(readStr,"+") == 0) {
            char key[MAX_LEN + 1];
            unsigned long long val;
            scanf("%s%llu", key, &val);
            for (int i = 0; i < strlen(key); ++i){
                key[i] = (char)tolower(key[i]);
            }
            NMyStd::TItem item;
            item.Value = val;
            std::memcpy(item.Key, key, sizeof(char)*(MAX_LEN+1));
            if (rbTree->Insert(item)) {
                printf("OK\n");
            } else {
                printf("Exist\n");
            }
        } else if (strcmp(readStr,"-") == 0) {
            char key[MAX_LEN + 1];
            scanf("%s", key);
            for (int i = 0; i < strlen(key); ++i){
                key[i] = (char)tolower(key[i]);
            }
            if (rbTree->Remove(key)) {
                printf("OK\n");
            } else {
                printf("NoSuchWord\n");
            }
        } else if (strcmp(readStr,"!") == 0) {
            char path[MAX_LEN + 1];
            scanf("%s %s", readStr, path);
            bool isOK = true;
            if (strcmp(readStr,"Save") == 0) {
                NMyStd::TRBTree::Save(path, *rbTree, isOK);
                if (isOK) {
                    printf("OK\n");
                }
            }  else {
                NMyStd::TRBTree* tmpTreePtr = new NMyStd::TRBTree;
                NMyStd::TRBTree::Load(path, *tmpTreePtr, isOK);
                if (isOK) {
                    printf("OK\n");
                    delete rbTree;
                    rbTree = tmpTreePtr;
                } else {
                    delete tmpTreePtr;
                }
            }
        } else {
            for (int i = 0; i < strlen(readStr); ++i){
                readStr[i] = (char)tolower(readStr[i]);
            }
            NMyStd::TItem ans;
            if (rbTree->Search(readStr, ans)) {
                printf("OK: %llu\n", ans.Value);
            } else {
                printf("NoSuchWord\n");
            }
        }
    }
    delete rbTree;
    return 0;
}

