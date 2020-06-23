CC := gcc
CFLAGS := -O3 -Wall -std=c99
LDFLAGS := -s -lm

.PHONY: all clean

all: fifo.x producer.x consumer.x prodcons.x

fifo.x: fifo.o
producer.x: producer.o
consumer.x: consumer.o
prodcons.x: prodcons.o

fifo.o: fifo.c
producer.o: producer.c
consumer.o: consumer.c
prodcons.o: prodcons.c


%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[ox])
