cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(std2 LANGUAGES CXX)

# Set global C++ standard for all subprojects
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories - each will be built independently
add_subdirectory(std2)
add_subdirectory(memory)
add_subdirectory(vector)
