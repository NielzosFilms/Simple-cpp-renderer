CXX = g++
CXXFLAGS = -Wall -g -Iinclude -Iimgui -Iimgui/backends
LDFLAGS = -lSDL2 -lGL -lGLEW

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

TARGET = $(BIN_DIR)/simple-cpp-renderer

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Build rules
all: lib-imgui $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) -Limgui -limgui

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
lib-imgui:
	$(MAKE) -C imgui

clean:
	rm -rf $(OBJS) $(BIN_DIR)/* $(OBJ_DIR)
	$(MAKE) -C imgui clean

run:
	$(TARGET)

.PHONY: all clean run lib-imgui