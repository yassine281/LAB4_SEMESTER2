cmake_minimum_required(VERSION 3.10)

# Project name and language
project(BST_Project LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Collect all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Define executable
add_executable(bst_test ${SOURCES})
add_custom_target(run
    COMMAND bst_test
    DEPENDS bst_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)