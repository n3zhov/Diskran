#ifndef SORT_HPP
#define SORT_HPP
#include "vector.hpp"
namespace mystd{
    struct item {
        char key [33];
        char value [2049];
    };

    void Counting_sort(vector<item> &data);
}
#endif
