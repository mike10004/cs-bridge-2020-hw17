#include <sstream>
#include <catch.hpp>
#include "../trees/avl.h"

TEST_CASE("AVL basics") {

    AVL<char> tree;
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