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
TEST_F(VectorTest, IndexOperator) {

    std2::vector<int> vals;
    vals.push_back(10);

    EXPECT_EQ(vals[0], 10);
}


