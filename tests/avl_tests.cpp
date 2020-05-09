#include <catch.hpp>
#include "../trees/avl.h"

TEST_CASE("AVL isInTree") {

    AVL<char> tree;
    tree.insert('a');
    tree.insert('m');
    tree.insert('d');
    bool found = tree.isInTree('m');
    REQUIRE(found);
}