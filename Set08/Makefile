CC := gcc
CFLAGS := -O3 -Wall -std=c99
LDFLAGS := -s -lpthread

.PHONY: all clean

all: exclusion.x

exclusion.x: exclusion.o
exclusion.o: exclusion.c


%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[ox])
