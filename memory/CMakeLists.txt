cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
)

# Add the library
add_library(memory SHARED src/unique_ptr.cpp)

# Add the executable for testing
# add_executable(test_memory tests/main.cpp)

# Link the library to the test executable
# target_link_libraries(test_memory memory)

# Specify C++23 standard for the target
# target_compile_features(test_memory PUBLIC cxx_std_23)
