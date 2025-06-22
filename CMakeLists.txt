cmake_minimum_required(VERSION 3.10...3.31 FATAL_ERROR)

project(std2 LANGUAGES CXX)

# Set global C++ standard for all subprojects
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing globally if TEST=true
if(UNITTEST)
    enable_testing()
endif()

# Include FetchContent for downloading dependencies
include(FetchContent)

# Download and configure Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add subdirectories - each will be built independently
add_subdirectory(std2)
add_subdirectory(memory)
add_subdirectory(vector)
add_subdirectory(list)
