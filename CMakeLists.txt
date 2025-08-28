cmake_minimum_required(VERSION 3.10)
project(BST_Project LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(include)

# Source files
file(GLOB SRC_SRCS "src/*.cpp")
file(GLOB TEST_SRCS "tests/*.cpp")

# UI executable
add_executable(bst_ui ${SRC_SRCS})

# Test executable
add_executable(bst_test ${SRC_SRCS} ${TEST_SRCS})

# Optional: run tests target
add_custom_target(run_test
    COMMAND bst_test
    DEPENDS bst_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
