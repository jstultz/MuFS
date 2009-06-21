CC = gcc
CFLAGS = -D_FILE_OFFSET_BITS=64
LIBS = -lfuse

all: bin/mufs

bin/mufs: obj/mufs_fuse.o
	$(CC) $(CFLAGS) $(LIBS) -o bin/mufs obj/mufs_fuse.o

obj/mufs_fuse.o: src/mufs_fuse.c
	$(CC) $(CFLAGS) $(LIBS) -o obj/mufs_fuse.o -c src/mufs_fuse.c

.phony: clean

clean:
	rm -vf bin/* obj/*
