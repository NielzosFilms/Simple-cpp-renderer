CXX = g++
CXXFLAGS = -Wall -g -I. -Ibackends -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lGL

LIB_DIR = .
OBJ_DIR = ../build/imgui
BIN_DIR = bin

LIB_TARGET = libimgui.a

LIB_SRCS = $(wildcard $(LIB_DIR)/*.cpp)
LIB_BACKEND_SRCS = $(LIB_DIR)/backends/imgui_impl_opengl3.cpp $(LIB_DIR)/backends/imgui_impl_sdl2.cpp
LIB_OBJS = $(patsubst $(LIB_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(LIB_SRCS))
LIB_BACKEND_OBJS = $(patsubst $(LIB_DIR)/backends/%.cpp, $(OBJ_DIR)/backends/%.o, $(LIB_BACKEND_SRCS))

# Build rules
all: $(LIB_TARGET)

$(LIB_TARGET): $(LIB_OBJS) $(LIB_BACKEND_OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/backends/%.o: backends/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB_TARGET)

.PHONY: all clean