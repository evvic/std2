#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/vector.hpp"
#include <iostream>

template <typename T>
void print_vector(const std2::vector<T>& vect) {
    std::cout << '[';
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i];
        if (i < vect.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ']' << std::endl;
}


/*
 *
 */
struct Point3D {
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Point3D() {};
    Point3D(float scalar) : x(scalar), y(scalar), z(scalar) {}
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

    // Copy constructor
    Point3D(const Point3D& other)
        : x(other.x), y(other.y), z(other.z) {
        std::cout << "Point3D Copy Constructor called\n";
    }

    // Move constructor
    Point3D(Point3D&& other) noexcept
        : x(other.x), y(other.y), z(other.z) {
        other.x = 0.0f;
        other.y = 0.0f;
        other.z = 0.0f;
        std::cout << "Point3D Move Constructor called\n";
    }

    // Destructor
    ~Point3D() {
        std::cout << "Point3D Destructor called for (" << x << ", " << y << ", " << z << ")\n";
    }

    // Assignment operator
    Point3D& operator=(const Point3D& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            std::cout << "Point3D Copy Assignment called\n";
        }
        return *this;
    }

    // Move assignment operator
    Point3D& operator=(Point3D&& other) noexcept {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            std::cout << "Point3D Move Assignment called\n";
        }
        return *this;
    }

    // << operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const Point3D& point) {
        os << "Point3D(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }

};

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
}

// Test push_back and size
TEST_F(VectorTest, PushBackAndSize) {

    std2::vector<int> vals;
    vals.push_back(10);
    vals.push_back(20);
    vals.push_back(30);
    print_vector(vals);
    EXPECT_EQ(vals.size(), 3);

    std2::vector<Point3D> points;

    points.push_back(Point3D(1.0f, 2.0f, 3.0f));
    points.push_back(Point3D(1.0f));
    points.push_back(Point3D());

    print_vector(points);
}

// Test push_back and size
TEST_F(VectorTest, EmplaceBackAndSize) {

    std2::vector<int> vals;
    vals.emplace_back(10);
    vals.emplace_back(20);
    vals.emplace_back(30);
    print_vector(vals);
    EXPECT_EQ(vals.size(), 3);

    std2::vector<Point3D> points;

    points.emplace_back(1.0f, 2.0f, 3.0f);
    points.emplace_back(1.0f);
    points.emplace_back();

    print_vector(points);
}

// Test [] operator accessing elements
TEST_F(VectorTest, IndexOperator) {

    std2::vector<int> vals;
    vals.push_back(10);

    std::cout << "Replacing element at index 0 from " << 10 << " to " << 20 << std::endl;
    print_vector(vals);

    EXPECT_EQ(vals[0], 10);

    // Update an element
    vals[0] = 20;

    print_vector(vals);

    EXPECT_EQ(vals[0], 20);

    std2::vector<Point3D> points;
    
    // Add a point
    points.push_back(Point3D(1.0f, 2.0f, 3.0f));
    std::cout << "Initial vector: ";
    print_vector(points);
    
    // Get reference and modify
    Point3D& point_ref = points[0];
    point_ref.x = 10.0f;
    std::cout << "After modifying through reference: ";
    print_vector(points);
    EXPECT_EQ(points[0].x, 10.0f);
    
    // Direct assignment through operator[]
    points[0] = Point3D(20.0f, 20.0f, 20.0f);
    std::cout << "After direct assignment: ";
    print_vector(points);
    EXPECT_EQ(points[0].x, 20.0f);
    
    // Test const access
    const std2::vector<Point3D>& const_points = points;
    EXPECT_EQ(const_points[0].x, 20.0f);
    // Following line would not compile (good!):
    // const_points[0] = Point3D(); // Error: assignment of read-only location
}

// Test clear
TEST_F(VectorTest, Clear) {

    std2::vector<int> vals;
    vals.push_back(10);
    vals.push_back(10);
    vals.push_back(10);

    EXPECT_EQ(vals.size(), 3);

    vals.clear();

    EXPECT_EQ(vals.size(), 0);
}

// Test pop_back
TEST_F(VectorTest, PopBack) {

    std2::vector<int> vals;
    vals.push_back(10);
    vals.push_back(10);
    vals.push_back(10);

    EXPECT_EQ(vals.size(), 3);

    vals.pop_back();
    vals.pop_back();

    EXPECT_EQ(vals.size(), 1);
}

TEST_F(VectorTest, ReserveTest) {
    std2::vector<Point3D> points;
    
    // Add 100 points
    for(int i = 0; i < 100; i++) {
        points.push_back(Point3D(i, i, i));
    }
    
    std::cout << "Before reserve: size=" << points.size() << std::endl;
              
    points.reserve(50);
    
    std::cout << "After reserve(50): size=" << points.size() << std::endl;

    EXPECT_EQ(points.size(), 100);
}

TEST_F(VectorTest, ResizeTest) {
    std2::vector<Point3D> points;
    
    // First reserve space for 200
    points.reserve(200);
    
    // Add 100 points
    for(int i = 0; i < 100; i++) {
        points.push_back(Point3D(i, i, i));
    }
    
    std::cout << "Initial state: size=" << points.size() << std::endl;
              
    // Now resize to 50
    points.resize(50);
    
    std::cout << "After resize(50): size=" << points.size() << std::endl;

    // Now resize to 100
    points.resize(100, Point3D(1.0f, 1.0f, 1.0f));
    
    std::cout << "After resize(100): size=" << points.size() << std::endl;

}

TEST_F(VectorTest, ResizeWithValue) {
    std2::vector<Point3D> points;
    
    // Resize to 3 elements, all with value (1,1,1)
    points.resize(3, Point3D(1.0f));
    
    EXPECT_EQ(points.size(), 3);
    for(size_t i = 0; i < points.size(); ++i) {
        EXPECT_EQ(points[i].x, 1.0f);
        EXPECT_EQ(points[i].y, 1.0f);
        EXPECT_EQ(points[i].z, 1.0f);
    }
}
