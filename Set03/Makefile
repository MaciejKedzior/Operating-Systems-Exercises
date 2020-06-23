CC := gcc
CFLAGS := -O3 -Wall -std=c99
LDFLAGS := -s -lm

.PHONY: all clean

all: handling.x send.x group.x

handling.x: handling.o procinfo.o 
handling.o: handling.c

send.x: send.o procinfo.o
send.o: send.c

group.x: group.o procinfo.o
group.o: group.c

procinfo.o: procinfo.c procinfo.h


%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[ox])
