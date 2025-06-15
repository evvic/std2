cmake_minimum_required(VERSION 3.10...3.31 FATAL_ERROR)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
)

# Add the library (currently empty but prepared for future implementation)
add_library(vector INTERFACE)

# Link against core std2 library
target_link_libraries(vector INTERFACE std2)

# Set C++23 standard for this target
target_compile_features(vector INTERFACE cxx_std_23)
