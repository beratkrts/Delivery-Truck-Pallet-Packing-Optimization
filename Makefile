CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -I./Code

SRC_DIR = Code
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) \
       $(wildcard $(SRC_DIR)/cli/*.cpp) \
       $(wildcard $(SRC_DIR)/input/*.cpp) \
       $(wildcard $(SRC_DIR)/algorithms/*.cpp) \
       $(wildcard $(SRC_DIR)/utils/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable
TARGET = $(BIN_DIR)/delivery_truck_optimizer

# Documentation
DOC_DIR = Documentation
DOXYFILE = $(DOC_DIR)/Doxyfile

.PHONY: all clean doc directories

all: directories $(TARGET)

directories:
	@mkdir -p $(OBJ_DIR)/cli
	@mkdir -p $(OBJ_DIR)/input
	@mkdir -p $(OBJ_DIR)/algorithms
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

doc:
	@mkdir -p $(DOC_DIR)
	doxygen $(DOXYFILE)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)/html 