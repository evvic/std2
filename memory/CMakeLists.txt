cmake_minimum_required(VERSION 3.10...3.31 FATAL_ERROR)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
)

# Create library target
add_library(memory SHARED src/unique_ptr.cpp)

# Create test directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Add the test executable
add_executable(memory_tests
    tests/unique_ptr_test.cpp
)

# Link against gtest and memory library
target_link_libraries(memory_tests
    PRIVATE
        memory
        GTest::gtest_main
        GTest::gmock_main
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(memory_tests)

# Add the executable for testing
# add_executable(test_memory tests/main.cpp)

# Link the library to the test executable
# target_link_libraries(test_memory memory)

# Specify C++23 standard for the target
# target_compile_features(test_memory PUBLIC cxx_std_23)
