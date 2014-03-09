CFLAGS=-g -Wall -march=native
CC=gcc
SRCS=io.c tlb.c translate.c pagetable.c binary.c
OBJS=io.o tlb.o translate.o pagetable.o binary.o
LDFLAGS=
LIBS=

all:    translate

$(SRCS):
	$(CC) $(CFLAGS) -c $*.c

translate: $(OBJS)
	$(CC) $(LDFLAGS) $(LIBS) -o translate $(OBJS)

clean:
	rm -f *.o translate
