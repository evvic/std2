cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# Create the core std2 library
add_library(std2 INTERFACE)

# Set include directories for this library
target_include_directories(std2 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set C++23 standard for this target
target_compile_features(std2 INTERFACE cxx_std_23)
