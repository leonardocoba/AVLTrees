
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/
#define private public
#include "../src/AVL.h"

TEST_CASE("BST Insert", "[flag]"){

    MyAVLTree tree;   // Create a Tree object
    tree.insert("Adam", "10000000");
    tree.insert("Sarah", "20000000");
    tree.insert("Steve", "30000000");
    std::vector<int> actualOutput = tree.inorder();
    std::vector<int> expectedOutput = {1, 2, 3};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
	REQUIRE(test == 1);
}

