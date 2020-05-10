#ifndef HW17_TREES_TESTING_H
#define HW17_TREES_TESTING_H

#include <cstdlib>
#include <catch.hpp>
#include "../trees/tree.h"

void TestTree(Tree<int>& tree) {
    for (int i = 0; i < 25; i++){
        int val = rand() % 1000;
        tree.insert(val);
        REQUIRE(tree.check());
    }
}



#endif //HW17_TREES_TESTING_H
