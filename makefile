##Directories
SRC_DIR := src
INC_DIR := include
TEST_DIR := $(SRC_DIR)/tests
OBJ_DIR := obj
OBJ_TEST_DIR := $(OBJ_DIR)/tests
BIN_DIR := bin

##Compiler flags
CXX := clang++

CXXFLAGS := -std=c++20 -g -Wall -Wextra -Werror -Wno-unused-function -I$(INC_DIR) $(addprefix -I, $(wildcard $(INC_DIR)/*))

##Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_TEST_DIR)/%.o, $(TEST_SRCS))
DBG_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%_d.o, $(SRCS))
TEST_DBG_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_TEST_DIR)/%_d.o, $(TEST_SRCS))

##Binaries
TARGET := $(BIN_DIR)/DataStructureTest
DBG_TARGET := $(BIN_DIR)/DataStructureTestD

all : debug release

release : $(TARGET)

debug : $(DBG_TARGET)


$(TARGET) : $(TEST_OBJS) $(OBJS) | $(BIN_DIR)
	@echo "Linking release build...."
	$(CXX) $(CXXFLAGS) -lgtest -lgmock -lpthread -o $@ $^
	@echo "Linking release build completed"

$(DBG_TARGET) : $(TEST_DBG_OBJS) $(DBG_OBJS) | $(BIN_DIR)
	@echo "Linking debug build...."
	$(CXX) $(CXXFLAGS) -lgtest -lgmock -lpthread -o $@ $^
	@echo "Linking debug build completed"

$(OBJ_TEST_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_TEST_DIR)
	@echo "Compiling test release build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling test release build completed"

$(OBJ_TEST_DIR)/%_d.o: $(TEST_DIR)/%.cpp | $(OBJ_TEST_DIR)
	@echo "Compiling test debug build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@ -DDEBUG
	@echo "Compiling test debug build completed"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling release build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling release build completed"

$(OBJ_DIR)/%_d.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling debug build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@ -DDEBUG
	@echo "Compiling debug build completed"

$(OBJ_TEST_DIR):
	mkdir -p $(OBJ_TEST_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning solution..."
	rm -rf $(OBJ_DIR) $(OBJ_TEST_DIR) $(BIN_DIR) $(TARGET) $(DBG_TARGET)
	@echo "Cleaning solution completed"

.PHONY: all release debug clean