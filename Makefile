.Phony: main clean

BIN_NAME=runify
CC=gcc
BIN_DIR=bin
SRC_DIR=src
CFLAGS=-I$(SRC_DIR) -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/cmocka
LDFLAGS=-lglib-2.0 -lcmocka

# Find all C source files in the source directory
SOURCES := $(wildcard $(SRC_DIR)/*.c)
# Exclude certain source files
EXCLUDES := $(SRC_DIR)/main.c
SOURCES := $(filter-out $(EXCLUDES), $(SOURCES))

# Make sure the bin directory exists before compiling anything
$(shell mkdir -p $(BIN_DIR))

main:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o $(BIN_DIR)/$(BIN_NAME) $(LDFLAGS)

test:
	$(CC) $(CFLAGS) test.c $(SOURCES) -o $(BIN_DIR)/$@ -g $(LDFLAGS)
	./$(BIN_DIR)/$@

clean:
	rm -f bin/$(BIN_NAME)
	rm -f bin/test
