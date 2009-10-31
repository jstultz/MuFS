CC = gcc
CFLAGS = -D_FILE_OFFSET_BITS=64
LIBS = -lfuse

OBJ_DIR = obj
BIN_DIR = bin
BIN_DIRS = $(OBJ_DIR) $(BIN_DIR)

all: $(BIN_DIR)/mufs

$(BIN_DIRS):
	if [ ! -d $@ ]; then mkdir -p $@; fi

$(BIN_DIR)/mufs: $(BIN_DIRS) $(OBJ_DIR)/mufs_fuse.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJ_DIR)/mufs_fuse.o

$(OBJ_DIR)/mufs_fuse.o: $(BIN_DIRS) src/mufs_fuse.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ -c src/mufs_fuse.c

.phony: clean

clean:
	rm -rvf $(BIN_DIRS)
