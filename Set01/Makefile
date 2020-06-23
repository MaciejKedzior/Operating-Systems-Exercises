CC := gcc
CFLAGS := -O3 -Wall -std=c99
LDFLAGS := -s -lm

.PHONY: all clean tar

all: main.x copy.x processes.x lider.x 

main.x: main.o procinfo.o
main.o: main.c procinfo.h
procinfo.o: procinfo.c procinfo.h
copy.x: copy.o
copy.o: copy.c
processes.x: processes.o procinfo.o 
processes.o: processes.c
lider.x: lider.o procinfo.o
lider.o: lider.c 


%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[ox])
