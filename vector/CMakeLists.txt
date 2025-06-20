cmake_minimum_required(VERSION 3.10...3.31 FATAL_ERROR)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
)

# Create library target
add_library(vector SHARED src/vector.cpp)

# Create test directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Add the test executable
add_executable(vector_tests
    tests/vector_test.cpp
    tests/vector_allocator_test.cpp
)

# Link against gtest
target_link_libraries(vector_tests
    PRIVATE
        vector
        GTest::gtest_main
        GTest::gmock_main
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(vector_tests)

# Set C++23 standard for this target
# target_compile_features(vector INTERFACE cxx_std_23)
