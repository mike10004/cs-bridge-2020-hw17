#ifndef HW17_TREES_TESTING_H
#define HW17_TREES_TESTING_H

#include <cstdlib>
#include <catch.hpp>
#include "../trees/tree.h"

const int VALUE_MAX = 10000;

void TestTree(Tree<int>& tree) {
    int n = 1000;
    int t = 100;
    for (int j = 0; j < t; j++) {
        tree.clear();
        REQUIRE(tree.isEmpty());
        bool present[VALUE_MAX] = {false};
        for (int i = 0; i < n; i++) {
            int val = rand() % VALUE_MAX;
            tree.insert(val);
            present[val] = true;
            REQUIRE(!tree.isEmpty());
            // REQUIRE(tree.check());
        }
        for (int value = 0; value < VALUE_MAX; value++) {
            REQUIRE(present[value] == tree.isInTree(value));
        }
    }
}



#endif //HW17_TREES_TESTING_H
