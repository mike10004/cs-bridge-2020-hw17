add_definitions(-DUNIT_TESTS)
add_executable(hw17_tests
        ../trees/avl.h
        ../trees/AVL.cpp
        avl_tests.cpp
        tests_main.cpp
        trees_testing.h)
