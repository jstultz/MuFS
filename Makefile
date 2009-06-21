CC = gcc
CFLAGS = -D_FILE_OFFSET_BITS=64

all: bin/mufs

bin/mufs: obj/mufs_fuse.o
	$(CC) $(CFLAGS) -o bin/mufs obj/mufs_fuse.o

obj/mufs_fuse.o: src/mufs_fuse.c
	$(CC) $(CFLAGS) -o obj/mufs_fuse.o -c src/mufs_fuse.c

.phony: clean

clean:
	rm -vf bin/* obj/*