
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/vector.hpp"

// Custom allocator that tracks allocations/deallocations
template<typename T>
class TrackingAllocator {
public:
    using value_type = T;

    static size_t allocate_count;
    static size_t deallocate_count;

    TrackingAllocator() noexcept {}
    
    template<typename U>
    TrackingAllocator(const TrackingAllocator<U>&) noexcept {}

    T* allocate(size_t n) {
        allocate_count++;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_t) {
        deallocate_count++;
        ::operator delete(p);
    }
};

template<typename T>
size_t TrackingAllocator<T>::allocate_count = 0;

template<typename T>
size_t TrackingAllocator<T>::deallocate_count = 0;

class AllocatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset counters before each test
        TrackingAllocator<int>::allocate_count = 0;
        TrackingAllocator<int>::deallocate_count = 0;
    }
};

// Test default allocator
TEST_F(AllocatorTest, DefaultAllocator) {
    std2::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    EXPECT_EQ(vec.size(), 3);
}

// Test custom allocator construction and basic operations
TEST_F(AllocatorTest, CustomAllocatorBasic) {
    TrackingAllocator<int> alloc;
    std2::vector<int, TrackingAllocator<int>> vec(alloc);
    
    EXPECT_EQ(TrackingAllocator<int>::allocate_count, 1); // Initial allocation
    
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    EXPECT_EQ(vec.size(), 3);
}

// Test allocator behavior during reallocation
TEST_F(AllocatorTest, CustomAllocatorReallocation) {
    TrackingAllocator<int> alloc;
    std2::vector<int, TrackingAllocator<int>> vec(alloc);
    
    // Fill vector to force reallocation
    for(int i = 0; i < 10; i++) {
        vec.push_back(i);
    }
    
    // Should have reallocated at least once
    EXPECT_GT(TrackingAllocator<int>::allocate_count, 1);
    EXPECT_GT(TrackingAllocator<int>::deallocate_count, 0);
}

// Test allocator behavior during resize
TEST_F(AllocatorTest, CustomAllocatorResize) {
    TrackingAllocator<int> alloc;
    std2::vector<int, TrackingAllocator<int>> vec(alloc);
    
    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
    
    vec.resize(10);
    EXPECT_EQ(vec.size(), 10);
    
    vec.resize(3);
    EXPECT_EQ(vec.size(), 3);
}
