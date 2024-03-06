# TODO: make this better... How? IDFK
CC = gcc
CFLAGS = -Wall -Werror -std=c99

SRC_DIR = src
BUILD_DIR = build

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

TARGET = compiler

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGET)

run:
	./$(TARGET)
