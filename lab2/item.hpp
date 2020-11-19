//
// Created by nikita on 18.11.2020.
//

#ifndef LAB2_ITEM_HPP
#define LAB2_ITEM_HPP
const long long MAX_LEN = 256;
namespace NMyStd{
    struct TItem{
        unsigned long long Value;
        char Key[MAX_LEN+1];
    };
}
#endif //LAB2_ITEM_HPP
