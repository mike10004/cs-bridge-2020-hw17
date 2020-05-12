add_definitions(-DUNIT_TESTS)
add_executable(hw17_tests
        ../trees/redblack.h
        ../trees/redblack.cpp
        redblacktree_tests.cpp
        tests_main.cpp
        trees_testing.h ../trees/redblack.cpp)
