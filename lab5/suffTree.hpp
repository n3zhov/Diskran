#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define TERMINATION_SYMBOL '$'

using namespace std;

class TSuffixTree;

class TNode
{
private:
    map<char, TNode *> Children; 
    TNode *SuffixLink;
    int Start;
    int *End;
    int SuffixIndex;
public:
    friend TSuffixTree;


    TNode(TNode *link, int start, int *end) : TNode(link, start, end, -1){
    }


    TNode(TNode *link, int start, int *end, int ind) :
    SuffixLink(link),Start(start),End(end),SuffixIndex(ind){
    }
};

class TSuffixTree
{
private:
    void LinHelp(TNode *curr, int n, std::string &res){
        if (!curr)
            return;
        for (auto it : curr->Children) {
            LinHelp(it.second, n, res);
            if(res != "") {
                return;
            }
        }
        if (curr->SuffixIndex != -1 && n <= *curr->End - curr->SuffixIndex + 1
            && Text[curr->SuffixIndex + n - 1] != TERMINATION_SYMBOL) {
            res = Text.substr(curr->SuffixIndex, n);
        }
    }
    void ExtendSuffixTree(int pos){

        LastCreatedInternalNode = nullptr;
        LeafEnd++;
        RemainingSuffixCount++;
        while (RemainingSuffixCount > 0){
            if (ActiveLength == 0) {
                ActiveEdge = pos;
            }

            auto find = ActiveNode->Children.find(Text[ActiveEdge]);

            if (find == ActiveNode->Children.end()){
                ActiveNode->Children.insert(make_pair(Text[ActiveEdge],
                                                      new TNode(Root, pos, &LeafEnd, pos - RemainingSuffixCount + 1)));

                if (LastCreatedInternalNode != nullptr){
                    LastCreatedInternalNode->SuffixLink = ActiveNode;
                    LastCreatedInternalNode = nullptr;
                }
            }
            else{

                TNode *next = find->second;
                int edge_length = EdgeLength(next);

                if (ActiveLength >= edge_length){
                    ActiveEdge += edge_length;
                    ActiveLength -= edge_length;
                    ActiveNode = next;
                    continue;
                }

                if (Text[next->Start + ActiveLength] == Text[pos]){
                    if (LastCreatedInternalNode != nullptr && ActiveNode != Root) {
                        LastCreatedInternalNode->SuffixLink = ActiveNode;
                    }
                    ActiveLength++;
                    break; // выйдем из цикла while
                }

                TNode *split = new TNode(Root, next->Start, new int(next->Start + ActiveLength - 1));
                ActiveNode->Children[Text[ActiveEdge]] = split;
                next->Start += ActiveLength;
                split->Children.insert(make_pair(Text[pos], new TNode(Root, pos, &LeafEnd, pos - RemainingSuffixCount + 1)));
                split->Children.insert(make_pair(Text[next->Start], next));
                if (LastCreatedInternalNode != nullptr) {
                    LastCreatedInternalNode->SuffixLink = split;
                }
                LastCreatedInternalNode = split;
            }

            RemainingSuffixCount--;

            if (ActiveNode == Root && ActiveLength > 0){
                ActiveLength--;
                ActiveEdge++;
            }
            else if (ActiveNode != Root) {
                ActiveNode = ActiveNode->SuffixLink;
            }
        }
    }
    void DeleteSuffixTree(TNode *TNode){
        for (auto it : TNode->Children) {
            DeleteSuffixTree(it.second);
        }
        if (TNode->SuffixIndex == -1)
            delete TNode->End;
        delete TNode;
    }
    int EdgeLength(TNode *TNode){
        return *TNode->End - TNode->Start + 1;
    }


    TNode *Root = new TNode(nullptr, -1, new int(-1));
    TNode *LastCreatedInternalNode = nullptr;
    string Text;

    TNode *ActiveNode = nullptr;
    int ActiveEdge = -1;
    int ActiveLength = 0;
    int RemainingSuffixCount = 0;
    int LeafEnd = -1;
public:
    TSuffixTree(string &text){
        this->Text += text+TERMINATION_SYMBOL;
        BuildSuffixTree();
    }
    void BuildSuffixTree(){
        ActiveNode = Root;
        for (size_t i = 0; i < Text.length(); i++) {
            ExtendSuffixTree(i);
        }
    }
    std::string Linearization(int n){
        TNode *current = Root;
        std::string res = "";
        for (int i = 0; i < n; ++i){
            auto it = current->Children.begin();
            for (;it != current->Children.end(); ++it){
                LinHelp(it->second, n, res);
                if(res != ""){
                    break;
                }
            }
        }
        return res;
    }

    ~TSuffixTree() {
        DeleteSuffixTree(Root);
    }
};