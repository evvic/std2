#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/list.hpp"
#include <iostream>

template <typename T>
void print_list(std2::list<T> vals) {
    auto it = vals.begin();
    std::cout << '[';
    while (it.m_node) {
        std::cout << it.m_node->data << ", ";
        it++;
    }
    std::cout << ']' << std::endl;
}

class ListTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test basic construction and destruction
TEST_F(ListTest, BasicConstructionAndDestruction) {
    // Test default constructor
    std2::list<int> vals;
    vals.push_back(10);
    vals.push_back(20);
    vals.push_back(30);
    EXPECT_EQ(vals.size(), 3);
    print_list(vals);
}

// Test inserting
TEST_F(ListTest, InsertingWithIterator) {
    // Test default constructor
    std2::list<int> vals;
    vals.push_back(10);
    vals.push_back(20);

    auto it = vals.begin();
    it++;

    vals.insert(it, 11);
    vals.insert(it, 12);


    EXPECT_EQ(vals.size(), 4);
    print_list(vals);
}
