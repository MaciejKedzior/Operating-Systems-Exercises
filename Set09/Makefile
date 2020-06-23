CC := gcc
CFLAGS := -O3 -Wall -std=c99
LDFLAGS := -s -lpthread

.PHONY: all clean

all: bakery_counter.x 



bakery_counter.x: bakery_counter.o
bakery_counter.o: bakery_counter.c


%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[ox])
