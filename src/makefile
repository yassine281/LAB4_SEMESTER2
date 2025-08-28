# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Folders
SRC_DIR  := src
TEST_DIR := tests
OBJ_DIR  := build
BIN_DIR  := bin

# Source files
SRC_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)

# Object files
SRC_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Targets
UI_TARGET   := $(BIN_DIR)/bst_ui
TEST_TARGET := $(BIN_DIR)/bst_test

# Default: build both
all: $(UI_TARGET) $(TEST_TARGET)

# Link UI executable
$(UI_TARGET): $(SRC_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Link Test executable
$(TEST_TARGET): $(SRC_OBJS) $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test objects
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run UI
run_ui: $(UI_TARGET)
	./$(UI_TARGET)

# Run tests
run_test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run_ui run_test
