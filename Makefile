CC = gcc
CFLAGS = -D_FILE_OFFSET_BITS=64 -g
LIBS = -lfuse

INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
BIN_DIRS = $(OBJ_DIR) $(BIN_DIR)

all: $(BIN_DIR)/mufs

$(BIN_DIRS):
	if [ ! -d $@ ]; then mkdir -p $@; fi

$(BIN_DIR)/mufs: $(BIN_DIRS) $(OBJ_DIR)/fuse.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJ_DIR)/fuse.o

$(OBJ_DIR)/fuse.o: $(BIN_DIRS) src/fuse.c
	$(CC) $(CFLAGS) $(LIBS) -I$(INCLUDE_DIR) -o $@ -c src/fuse.c

.phony: clean

clean:
	rm -rvf $(BIN_DIRS)
