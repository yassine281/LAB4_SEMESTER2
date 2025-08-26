# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Folders
SRC_DIR  := src
OBJ_DIR  := build
BIN_DIR  := bin

# Target
TARGET   := $(BIN_DIR)/bst_test

# Sources/Objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
 @mkdir -p $(BIN_DIR)
 $(CXX) $(CXXFLAGS) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
 @mkdir -p $(OBJ_DIR)
 $(CXX) $(CXXFLAGS) -c $< -o $@

# Utilities
run: $(TARGET)
 ./$(TARGET)

clean:
 rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run