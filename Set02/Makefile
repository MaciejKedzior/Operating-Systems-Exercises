CC := gcc
CFLAGS := -O3 -Wall -std=c99
LDFLAGS := -s -lm

.PHONY: all clean

all: tree1.x tree2.x parent.x child.x zombie.x orphaned.x execute.x

execute.x: execute.o
orphaned.x: orphaned.o procinfo.o 
zombie.x: zombie.o procinfo.o
parent.x: parent.o procinfo.o
child.x: child.o procinfo.o
tree1.x: tree1.o procinfo.o
tree2.x: tree2.o procinfo.o

execute.o: execute.c
orphaned.o: orphaned.c
zombie.o: zombie.c procinfo.h
parent.o: parent.c procinfo.h
child.o: child.c procinfo.h
tree1.o: tree1.c procinfo.h
tree2.o: tree2.c procinfo.h

procinfo.o: procinfo.c procinfo.h


%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[ox])
