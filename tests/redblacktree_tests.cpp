#include <sstream>
#include <cstdlib>
#include <catch.hpp>
#include "../trees/tree.h"
#include "../trees/redblack.h"
#include "trees_testing.h"

TEST_CASE("RedBlackTree basics") {

    RedBlackTree<char> tree;
    REQUIRE(0 == tree.getSize());
    tree.insert('a');
    REQUIRE(1 == tree.getSize());
    tree.insert('m');
    REQUIRE(2 == tree.getSize());
    tree.insert('d');
    REQUIRE(3 == tree.getSize());
    bool found = tree.isInTree('m');
    REQUIRE(found);
    std::ostringstream buffer1;
    std::ostringstream buffer2;
    std::ostringstream buffer3;
    tree.printInOrder(buffer1);
    REQUIRE_FALSE(buffer1.str().empty());
    tree.printLevelOrder(buffer2);
    REQUIRE_FALSE(buffer2.str().empty());
    tree.printPostOrder(buffer3);
    REQUIRE_FALSE(buffer3.str().empty());
}

TEST_CASE("RedBlackTree Standard Test") {
    RedBlackTree<int> tree;
    srand(0x12345);
    TestTree(tree);
}

TEST_CASE("RedBlackTree contains") {
    srand(0x98765);
    RedBlackTree<int> tree;
    int n = 1000, k = 10000;
    std::set<int> values;
    for (int i = 0; i < n; i++){
        int val = rand() % k;
        tree.insert(val);
        values.insert(val);
    }
    for (int value = 0; value < k; value++) {
        bool present = values.find(value) != values.end();
        REQUIRE(present == tree.isInTree(value));
    }
}

