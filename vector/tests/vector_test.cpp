#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/vector.hpp"

class VectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test basic construction and destruction
TEST_F(VectorTest, BasicConstructionAndDestruction) {
    // Test default constructor
    std2::vector<int> vals;
    vals.push_back(10);
    vals.push_back(20);
    vals.push_back(30);
    EXPECT_EQ(vals.size(), 3);

    // Test constructor with pointer
    std2::unique_ptr<int> ptr2(new int(42));
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 42);
}

// Test push_back and size
TEST_F(VectorTest, VectorPushBackAndSize) {

    std2::vector<int> vals;
    vals.push_back(10);
    vals.push_back(20);
    vals.push_back(30);
    EXPECT_EQ(vals.size(), 3);
}

// Test push_back and size
TEST_F(VectorTest, VectorIndexOperator) {

    std2::vector<int> vals;
    vals.push_back(10);

    EXPECT_EQ(vals[0], 10);
}
