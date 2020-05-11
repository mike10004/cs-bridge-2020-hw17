#ifndef HW17_TREES_TESTING_H
#define HW17_TREES_TESTING_H

#include <cstdlib>
#include <catch.hpp>
#include "../trees/tree.h"

void TestTree(Tree<int>& tree) {
    int n = 1000;
    for (int i = 0; i < n; i++){
        int val = rand() % 10000;
        tree.insert(val);
        REQUIRE(!tree.isEmpty());
        REQUIRE(tree.check());
    }
}



#endif //HW17_TREES_TESTING_H
