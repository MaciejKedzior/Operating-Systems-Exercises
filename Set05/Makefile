CC := gcc
CFLAGS := -O3 -Wall -std=c99  -pthread 
LDFLAGS := -s -L. -lsem -lpthread -lrt

.PHONY: all clean

all: libsem.a semuse.x duplicator.x prog.x

libsem.a: sem.o
sem.o: sem.c
semuse.x: semuse.o
semuse.o: semuse.c sem.h
procinfo.o: procinfo.c procinfo.h
duplicator.x: duplicator.o procinfo.o
duplicator.o: duplicator.c sem.h
prog.x: prog.o procinfo.o
prog.o: prog.c 


libsem.a: sem.o
	ar rv $@ $<

%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[aox])
