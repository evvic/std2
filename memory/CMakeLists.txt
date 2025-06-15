cmake_minimum_required(VERSION 3.3, FATAL_ERROR)

project(memory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure the compiler supports C++23
# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#     if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
#         message(FATAL_ERROR "GCC version must be at least 14 for C++23 support")
#     endif()
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
#         message(FATAL_ERROR "Clang version must be at least 14 for C++23 support")
#     endif()
# else()
#     message(WARNING "Your compiler may not fully support C++23")
# endif()

# Include directories
include_directories(include)

# Add the library
add_library(memory SHARED src/unique_ptr.cpp)

# Add the executable for testing
add_executable(test_memory tests/main.cpp)

# Link the library to the test executable
target_link_libraries(test_memory memory)

# Specify C++23 standard for the target
target_compile_features(test_memory PUBLIC cxx_std_23)
