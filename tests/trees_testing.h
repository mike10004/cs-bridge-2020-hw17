#ifndef HW17_TREES_TESTING_H
#define HW17_TREES_TESTING_H

#include <cstdlib>
#include <catch.hpp>
#include "../trees/tree.h"

const int k = 10000;

void TestTree(Tree<int>& tree) {
    int n = 1000;
    bool present[k] = {false};
    for (int i = 0; i < n; i++){
        int val = rand() % k;
        tree.insert(val);
        present[val] = true;
        REQUIRE(!tree.isEmpty());
        REQUIRE(tree.check());
    }
    for (int value = 0; value < k; value++) {
        REQUIRE(present[value] == tree.isInTree(value));
    }
    tree.clear();
    REQUIRE(tree.isEmpty());
}



#endif //HW17_TREES_TESTING_H
