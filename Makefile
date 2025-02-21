CC=gcc
CCFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/app

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target: build the binary
all: $(TARGET)

# Link object files into the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# compile source files into obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

rebuild: clean all

.PHONY: all clean rebuild