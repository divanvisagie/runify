.Phony: main clean

BIN_NAME=runify
CC=gcc
BIN_DIR=bin
SRC_DIR=src
CFLAGS=-I$(SRC_DIR) -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/cmocka
LDFLAGS=-lglib-2.0 -lcmocka

# Release directory
RELEASE_DIR=./release
# Find all C source files in the source directory
SOURCES := $(wildcard $(SRC_DIR)/*.c)
# Exclude certain source files
EXCLUDES := $(SRC_DIR)/main.c
SOURCES := $(filter-out $(EXCLUDES), $(SOURCES))

PLATFORM=$(shell uname -s | tr '[:upper:]' '[:lower:]')
ARCH ?= $(shell uname -m | tr '[:upper:]' '[:lower:]')

# Make sure the bin directory exists before compiling anything
$(shell mkdir -p $(BIN_DIR))

main:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o $(BIN_DIR)/$(BIN_NAME) -g $(LDFLAGS)

build:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o $(BIN_DIR)/$(BIN_NAME) $(LDFLAGS)

run: main
	./$(BIN_DIR)/$(BIN_NAME)

test:
	$(CC) $(CFLAGS) test.c $(SOURCES) -o $(BIN_DIR)/$@ -g $(LDFLAGS)
	./$(BIN_DIR)/$@

clean:
	rm -f bin/$(BIN_NAME)
	rm -f bin/test

deb: build
	@sh ./scripts/build_deb.sh

deb-publish:
	@sh ./scripts/build_deb.sh "publish"

tarball: build
	@echo "Packaging the release..."
	@mkdir -p $(RELEASE_DIR);
	@cp docs/$(BIN_NAME).1 bin/$(BIN_NAME);
	@tar -czf $(RELEASE_DIR)/$(BIN_NAME)-$(PLATFORM)-$(ARCH).tar.gz -C bin/ $(BIN_NAME);

tarball-publish: tarball
	@TARBALL=$(BIN_NAME)-$(PLATFORM)-$(ARCH).tar.gz; \
	echo "Sending tarball $$TARBALL to script"; \
	sh ./scripts/publish_asset.sh $$TARBALL

