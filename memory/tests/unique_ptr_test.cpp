#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/unique_ptr.hpp"

class UniquePointerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test basic construction and destruction
TEST_F(UniquePointerTest, BasicConstructionAndDestruction) {
    // Test default constructor
    std2::unique_ptr<int> ptr1;
    EXPECT_EQ(ptr1.get(), nullptr);

    // Test constructor with pointer
    std2::unique_ptr<int> ptr2(new int(42));
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 42);
}

// Test move semantics
TEST_F(UniquePointerTest, MoveSemantics) {
    std2::unique_ptr<int> ptr1(new int(42));
    int* raw_ptr = ptr1.get();
    
    // Move construction
    std2::unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr1.get(), nullptr);  // NOLINT: testing moved-from state
    EXPECT_EQ(ptr2.get(), raw_ptr);
    
    // Move assignment
    std2::unique_ptr<int> ptr3;
    ptr3 = std::move(ptr2);
    EXPECT_EQ(ptr2.get(), nullptr);  // NOLINT: testing moved-from state
    EXPECT_EQ(ptr3.get(), raw_ptr);
}

// Test custom deleter
TEST_F(UniquePointerTest, CustomDeleter) {
    bool deleted = false;
    struct CustomDeleter {
        bool& deleted_ref;
        CustomDeleter(bool& ref) : deleted_ref(ref) {}
        void operator()(int* ptr) const {
            deleted_ref = true;
            delete ptr;
        }
    };

    {
        std2::unique_ptr<int, CustomDeleter> ptr(new int(42), CustomDeleter(deleted));
        EXPECT_FALSE(deleted);
    }
    EXPECT_TRUE(deleted);
}

// Performance test (useful for quant firms)
TEST_F(UniquePointerTest, PerformanceBenchmark) {
    const int iterations = 1000000;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        std2::unique_ptr<int> ptr(new int(i));
        *ptr = i * 2;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Log performance metrics
    std::cout << "Performance test completed in " << duration.count() << " microseconds\n";
    // Optional: Add EXPECT statements for performance thresholds if needed
}
