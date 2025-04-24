CC = cc
CFLAGS = -I ../src -Wall -g
OBJS = test-rbtree.o ../src/rbtree.o ../src/fixup.o ../src/deleteFixup.o ../src/transplant.o

test-rbtree: $(OBJS)
	$(CC) $(OBJS) -o test-rbtree

test-rbtree.o: test-rbtree.c
	$(CC) $(CFLAGS) -c -o test-rbtree.o test-rbtree.c

clean:
	rm -f test-rbtree *.o
.PHONY: clean
