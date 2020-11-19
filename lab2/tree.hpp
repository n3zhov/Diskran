
#ifndef DISKRAN_TREE_HPP
#define DISKRAN_TREE_HPP
#include "item.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

namespace NMyStd{
    struct TRBNode {
        int Color = 0;
        //0 - чёрный цвет, 1 - красный
        TRBNode* Parent;
        TRBNode* Left;
        TRBNode* Right;
        TItem Data;
        TRBNode(): Color(0), Parent(NULL), Left(NULL), Right(NULL), Data() {}
        TRBNode(const TItem& p): Color(0), Parent(NULL), Left(NULL), Right(NULL), Data(p) {}
        ~TRBNode() = default;
    };

    class TRBTree{
        TRBNode* Root;
        bool Search(char* key, TItem& res, TRBNode* node);
        bool Insert(const TItem& Data, TRBNode* node);
        void Remove(TRBNode* node);
        void RemoveFixUp(TRBNode* node, TRBNode* nodeParent);
        void LeftRotate(TRBNode* node);
        void RightRotate(TRBNode* node);
        void InsertFixUp(TRBNode* node);
        void DeleteTree(TRBNode* node);
        static void RecursiveLoad(std::ifstream& fs, TRBNode*& node, bool &isOK);
        static void RecursiveSave(std::ofstream& fs, TRBNode* node, bool &isOK);

    public:
        TRBTree(): Root(NULL) {};
        TRBNode* GetRoot(){
            return Root;
        }
        bool Search(char key[MAX_LEN + 1], TItem& res);
        bool Insert(const TItem& Data);
        bool Remove(const char key[MAX_LEN + 1]);
        static void Load(const char path[MAX_LEN + 1], TRBTree& t, bool& isOK);
        static void Save(const char path[MAX_LEN + 1], TRBTree& t, bool& isOK);
        ~TRBTree();
    };

    bool TRBTree::Search(char key[MAX_LEN + 1], TItem& res) {
        return Search(key, res, Root);
    }
    bool TRBTree::Search(char key[MAX_LEN + 1], TItem& res,TRBNode* node) {
        if (node == NULL) {
            return false;
        } else if (strcmp(key, node->Data.Key) == 0) {
            res = node->Data;
            return true;
        } else {
           TRBNode* to = (strcmp(key, node->Data.Key) < 0) ? node->Left : node->Right;
            return Search(key, res, to);
        }
    }
    // конец функций для поиска в дереве

    // функции для вставки в дерево
    bool TRBTree::Insert(const TItem& data) {
        if (Root == NULL) {
            Root = new TRBNode(data);
            Root->Color=0;
            return true;
        } else {
            return Insert(data, Root);
        }
    }

   
    bool TRBTree::Insert(const TItem& data, TRBNode* node) {
        const char* key = data.Key;
        if (strcmp(key, node->Data.Key) == 0) {
            return false;
        } else if (strcmp(key, node->Data.Key) < 0) {
            if (node->Left == NULL) {
                node->Left = new TRBNode(data);
                node->Left->Parent = node;
                node->Left->Color = 1;
                if (node->Color == 1) {
                    InsertFixUp(node->Left);
                }
                return true;
            } else {
                return Insert(data, node->Left);
            }
        } else {
            if (node->Right == NULL) {
                node->Right = new TRBNode(data);
                node->Right->Parent = node;
                node->Right->Color = 1;
                if (node->Color == 1) {
                    InsertFixUp(node->Right);
                }
                return true;
            } else {
                return Insert(data, node->Right);
            }
        }
    }

    void TRBTree::InsertFixUp(TRBNode* node) {
        TRBNode* grandParent = node->Parent->Parent;
        if (grandParent->Left == node->Parent) {
            if (grandParent->Right != NULL && grandParent->Right->Color == 1) {
                grandParent->Left->Color = 0;
                grandParent->Right->Color = 0;
                grandParent->Color = 1;
                if (Root == grandParent) {
                    grandParent->Color = 0;
                    return;
                }
                if (grandParent->Parent != NULL && grandParent->Color == 1 && grandParent->Parent->Color == 1) {
                    InsertFixUp(grandParent);
                }
                return;
            } else if (grandParent->Right == NULL ||
                       (grandParent->Right != NULL && grandParent->Right->Color == 0)) {
                if (node == node->Parent->Left) {
                    grandParent->Color = 1;
                    node->Parent->Color = 0;
                    RightRotate(grandParent);
                    return;
                } else {
                    LeftRotate(node->Parent);
                    node->Color = 0;
                    node->Parent->Color = 1;
                    RightRotate(node->Parent);
                    return;
                }
            }
        } else {
            if (grandParent->Left != NULL && grandParent->Left->Color == 1) {
                grandParent->Right->Color = 0;
                grandParent->Left->Color = 0;
                grandParent->Color = 1;
                if (Root == grandParent) {
                    grandParent->Color = 0;
                    return;
                }
                if (grandParent->Parent != NULL && grandParent->Color == 1 && grandParent->Parent->Color == 1) {
                    InsertFixUp(grandParent);
                }
                return;
            } else if (grandParent->Left == NULL ||
                       (grandParent->Left != NULL && grandParent->Left->Color == 0 )) {
                if (node == node->Parent->Right) {
                    grandParent->Color = 1;
                    node->Parent->Color = 0;
                    LeftRotate(grandParent);
                    return;
                } else {
                    RightRotate(node->Parent);
                    node->Color = 0;
                    node->Parent->Color = 1;
                    LeftRotate(node->Parent);
                    return;
                }
            }
        }
    }
    // конец функций для вставки в дерево

    // функции для удаления из дерева
    bool TRBTree::Remove(const char key[MAX_LEN + 1]) {
        TRBNode* node = Root;
        while (node != NULL && strcmp(key, node->Data.Key) != 0) {
            TRBNode* to = (strcmp(key, node->Data.Key) < 0) ? node->Left : node->Right;
            node = to;
        }
        if (node == NULL) {
            return false;
        }
        Remove(node);
        return true;
    }

    void TRBTree::Remove(TRBNode* node) {
        TRBNode* toDelete = node;
        int toDeleteColor = toDelete->Color;
        TRBNode* toReplace;
        TRBNode* toReplaceParent;
        if (node->Left == NULL) {
            toReplace = node->Right;
            if (toReplace != NULL) {
                toReplace->Parent = node->Parent;
                toReplaceParent = node->Parent;
            } else {
                toReplaceParent = node->Parent;
                if (node == Root) {
                    toReplaceParent = NULL;
                    Root = NULL;
                }
            }
            if (node->Parent != NULL) {
                if (node->Parent->Left == node) {
                    node->Parent->Left = toReplace;
                } else {
                    node->Parent->Right = toReplace;
                }
            } else {
                Root = toReplace;
            }
        } else if (node->Right == NULL) {
            toReplace = node->Left;
            toReplace->Parent = node->Parent;
            toReplaceParent = node->Parent;
            if (node->Parent != NULL) {
                if (node->Parent->Left == node) {
                    node->Parent->Left = toReplace;
                } else {
                    node->Parent->Right = toReplace;
                }
            } else {
                Root = toReplace;
            }
        } else {
            TRBNode* minInRight = node->Right;
            while(minInRight->Left != NULL) {
                minInRight = minInRight->Left;
            }
            toDelete = minInRight;
            toDeleteColor = toDelete->Color;
            toReplace = toDelete->Right;
            if (toDelete->Parent == node) {
                if (toReplace != NULL) {
                    toReplace->Parent = toDelete;
                }
                toReplaceParent = toDelete;
            } else {
                toDelete->Parent->Left = toReplace;
                if (toReplace != NULL) {
                    toReplace->Parent = toDelete->Parent;
                }
                toReplaceParent = toDelete->Parent;
                toDelete->Right = node->Right;
                toDelete->Right->Parent = toDelete;
            }
            if (node->Parent != NULL) {
                if (node->Parent->Left == node) {
                    node->Parent->Left = toDelete;
                } else {
                    node->Parent->Right = toDelete;
                }
            } else {
                Root = toDelete;
            }
            toDelete->Parent = node->Parent;
            toDelete->Left = node->Left;
            toDelete->Left->Parent = toDelete;
            toDelete->Color = node->Color;
        }
        if (toDeleteColor == 0) {
            RemoveFixUp(toReplace, toReplaceParent);
        }
        delete node;
    }

    void TRBTree::RemoveFixUp(TRBNode* node, TRBNode* nodeParent) {
        while ((node == NULL || node->Color == 0) && node != Root) {
            TRBNode* brother;
            if (node == nodeParent->Left) {
                brother = nodeParent->Right;
                if (brother->Color == 1) {
                    brother->Color = 0;
                    nodeParent->Color = 1;
                    LeftRotate(nodeParent);
                    brother = nodeParent->Right;
                }
                if (brother->Color == 0) {
                    if ((brother->Left == NULL || brother->Left->Color == 0)
                        && (brother->Right == NULL || brother->Right->Color == 0)) {
                        brother->Color = 1;
                        node = nodeParent;
                        if (node != NULL) {
                            nodeParent = node->Parent;
                        }
                    } else {
                        if (brother->Right == NULL || brother->Right->Color == 0) {
                            brother->Left->Color = 0;
                            brother->Color = 1;
                            RightRotate(brother);
                            brother = nodeParent->Right;
                        }
                        brother->Color = nodeParent->Color;
                        nodeParent->Color = 0;
                        brother->Right->Color = 0;
                        LeftRotate(nodeParent);
                        break;
                    }
                }
            } else {
                brother = nodeParent->Left;
                if (brother->Color == 1) {
                    brother->Color = 0;
                    nodeParent->Color = 1;
                    RightRotate(nodeParent);
                    brother = nodeParent->Left;
                }
                if (brother->Color == 0) {
                    if ((brother->Right == NULL || brother->Right->Color == 0)
                        && (brother->Left == NULL || brother->Left->Color == 0)) {
                        brother->Color = 1;
                        node = nodeParent;
                        if (node != NULL) {
                            nodeParent = node->Parent;
                        }
                    } else {
                        if (brother->Left == NULL || brother->Left->Color == 0) {
                            brother->Right->Color = 0;
                            brother->Color = 1;
                            LeftRotate(brother);
                            brother = nodeParent->Left;
                        }
                        brother->Color = nodeParent->Color;
                        nodeParent->Color = 0;
                        brother->Left->Color = 0;
                        RightRotate(nodeParent);
                        break;
                    }
                }
            }
        }
        if (node != NULL) {
            node->Color = 0;
        }
    }
    // конец функций для удаления из дерева

    // левый и правый повороты
    void TRBTree::LeftRotate(TRBNode* node) {
        TRBNode* rightSon = node->Right;
        if (rightSon == NULL) {
            return;
        }
        node->Right = rightSon->Left;
        if (rightSon->Left != NULL) {
            rightSon->Left->Parent = node;
        }
        rightSon->Parent = node->Parent;
        if (node->Parent == NULL) {
            Root = rightSon;
        } else if (node == node->Parent->Left) {
            node->Parent->Left = rightSon;
        } else {
            node->Parent->Right = rightSon;
        }
        rightSon->Left = node;
        node->Parent = rightSon;
    }

    void TRBTree::RightRotate(TRBNode* node) {
        TRBNode* leftSon = node->Left;
        if (leftSon == NULL) {
            return;
        }
        node->Left = leftSon->Right;
        if (leftSon->Right != NULL) {
            leftSon->Right->Parent = node;
        }
        leftSon->Parent = node->Parent;
        if (node->Parent == NULL) {
            Root = leftSon;
        } else if (node == node->Parent->Right) {
            node->Parent->Right = leftSon;
        } else {
            node->Parent->Left = leftSon;
        }
        leftSon->Right = node;
        node->Parent = leftSon;
    }
    // конец левого и правого поворотов

    // функции для загрузки и выгрузки дерева в файл
    void TRBTree::RecursiveLoad(std::ifstream& fs, TRBNode*& node, bool& isOK) {
        if (!isOK) {
            return;
        }
        TItem data;
        short len = 0;
        fs.read((char*)&len, sizeof(short));
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to read from file\n";
            isOK = false;
            return;
        }
        if (len == -1) {
            return;
        } else if (len != -1 && (len <= 0 || len > MAX_LEN)) {
            std::cerr << "ERROR: Wrong file format\n";
            isOK = false;
            return;
        }
        char color;
        for (int i = 0; i < len; ++i) {
            fs.read(&(data.Key[i]), sizeof(char));
            if (isalpha(data.Key[i]) == 0) {
                std::cerr << "ERROR: Wrong file format\n";
                isOK = false;
                return;
            }
        }
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to read from file\n";
            isOK = false;
            return;
        }
        data.Key[len] = '\0';
        fs.read((char*)&data.Value, sizeof(unsigned long long));
        if (fs.bad()) {
            std::cerr << "Unable to read from file\n";
            isOK = false;
            return;
        }
        fs.read((char*)&color, sizeof(char));
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to read from file\n";
            isOK = false;
            return;
        }
        node = new TRBNode(data);
        if (color == 'r') {
            node->Color = 1;
        } else if (color == 'b') {
            node->Color = 0;
        } else {
            std::cout << "ERROR: Wrong file format\n";
            isOK = false;
            return;
        }
        RecursiveLoad(fs, node->Left, isOK);
        RecursiveLoad(fs, node->Right, isOK);
        if (node->Left != NULL) {
            node->Left->Parent = node;
        }
        if (node->Right != NULL) {
            node->Right->Parent = node;
        }
    }

    void TRBTree::Load(const char* path, TRBTree& t, bool& isOK) {
        std::ifstream fs;
        fs.open(path, std::ios::binary);
        if (fs.fail()) {
            std::cerr << "ERROR: Unable to open file " << path << " in read mode\n";
            isOK = false;
            return;
        }
        RecursiveLoad(fs, t.Root, isOK);
        fs.close();
        if (fs.fail()) {
            std::cerr << "ERROR: Unable to close file " << path << "\n";
            isOK = false;
            return;
        }
    }

    void TRBTree::RecursiveSave(std::ofstream& fs, TRBNode* t, bool& isOK) {
        if (!isOK) {
            return;
        }
        short len = 0;
        if (t == NULL) {
            len = -1;
            fs.write((char*)&len, sizeof(short));
            if (fs.bad()) {
                std::cerr << "ERROR: Unable to write in file\n";
                isOK = false;
                return;
            }
            return;
        }
        char color = t->Color == 0 ? 'b' : 'r';
        for (int i = 0; i < MAX_LEN && t->Data.Key[i] != '\0' && isalpha(t->Data.Key[i]) != 0; ++i) {
            len++;
        }
        fs.write((char*)&len, sizeof(short));
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to write in file\n";
            isOK = false;
            return;
        }
        fs.write(t->Data.Key, sizeof(char) * len);
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to write in file\n";
            isOK = false;
            return;
        }
        fs.write((char*)&(t->Data.Value), sizeof(unsigned long long));
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to write in file\n";
            isOK = false;
            return;
        }
        fs.write((char*)&color, sizeof(char));
        if (fs.bad()) {
            std::cerr << "ERROR: Unable to write in file\n";
            isOK = false;
            return;
        }
        RecursiveSave(fs, t->Left, isOK);
        RecursiveSave(fs, t->Right, isOK);
    }

    void TRBTree::Save(const char* path, TRBTree& t, bool& isOK) {
        std::ofstream fs;
        fs.open(path, std::ios::binary);
        if (fs.fail()) {
            std::cerr << "ERROR: Unable to open file " << path << " in write mode\n";
            isOK = false;
            return;
        }
        RecursiveSave(fs, t.Root, isOK);
        fs.close();
        if (fs.fail()) {
            std::cerr << "ERROR: Unable to close file " << path << "\n";
            isOK = false;
            return;
        }
    }
    // конец функции для загрузки и выгрузки дерева в файл

    // деструктор дерева
    void TRBTree::DeleteTree(TRBNode* node) {
        if (node == NULL) {
            return;
        } else {
            DeleteTree(node->Left);
            DeleteTree(node->Right);
            delete node;
        }
    }

    TRBTree::~TRBTree() {
        DeleteTree(Root);
        Root = NULL;
    }
}
#endif //DISKRAN_TREE_HPP
