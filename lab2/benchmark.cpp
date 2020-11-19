#include <cstring>
#include <cctype>
#include <map>
#include <chrono>
#include "item.hpp"
#include "tree.hpp"

int main(){
    using duration_t = std::chrono::microseconds;
    char readStr[MAX_LEN+1];
    std::map<char*, unsigned long long> mapTree;
    NMyStd::TRBTree* rbTree = new NMyStd::TRBTree;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    unsigned long long  mapTsInsert = 0, mapTsDelete = 0, mapTsSearch = 0;
    unsigned long long  rbTsInsert = 0, rbTsDelete = 0, rbTsSearch = 0;
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
            start = std::chrono::system_clock::now();
            rbTree->Insert(item);
            end = std::chrono::system_clock::now();
            rbTsInsert += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mapTree.insert({key, val});
            end = std::chrono::system_clock::now();
            mapTsInsert += std::chrono::duration_cast<duration_t>( end - start ).count();
        } else if (strcmp(readStr,"-") == 0) {
            char key[MAX_LEN + 1];
            scanf("%s", key);
            for (int i = 0; i < strlen(key); ++i){
                key[i] = (char)tolower(key[i]);
            }
            start = std::chrono::system_clock::now();
            rbTree->Remove(key);
            end = std::chrono::system_clock::now();
            rbTsDelete += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mapTree.erase(key);
            end = std::chrono::system_clock::now();
            mapTsDelete += std::chrono::duration_cast<duration_t>( end - start ).count();
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

            start = std::chrono::system_clock::now();
            rbTree->Search(readStr, ans);
            end = std::chrono::system_clock::now();
            rbTsSearch += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mapTree.find(readStr);
            end = std::chrono::system_clock::now();
            mapTsSearch += std::chrono::duration_cast<duration_t>( end - start ).count();
        }
    }
    printf("==============START============\n");
    printf("INSERT std::map time: %llu ms\nINSERT rb tree time: %llu ms\n", mapTsInsert, rbTsInsert);
    printf("===============================\n");
    printf("DELETE std::map time: %llu ms\nDELETE rb tree time: %llu ms\n", mapTsDelete, rbTsDelete);
    printf("===============================\n");
    printf("SEARCH std::map time: %llu ms\nSEARCH rb tree time: %llu ms\n", mapTsSearch, rbTsSearch);
    printf("==============END==============\n");
    delete rbTree;
    return 0;
}

