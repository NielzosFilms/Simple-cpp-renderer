CC = g++
CFLAGS = -Wall -g -I$(HEADER_DIR)
LDFLAGS = -lSDL2 -lGL

SRC_DIR = src
HEADER_DIR = include
BUILD_DIR = build
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
EXEC = $(BIN_DIR)/simple-cpp-renderer

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/*

run:
	$(BIN_DIR)/simple-cpp-renderer

.PHONY: clean run