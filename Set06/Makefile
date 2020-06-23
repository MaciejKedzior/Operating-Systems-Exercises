CC := gcc
NAME := shmuse
EXEC1 := $(NAME)1.x
EXEC2 := $(NAME)2.x
OBJ := $(NAME).o
LIB_DIR := .
LIB_NAME := shmem
LIB_SEM := sem
LDLIBS := -lrt -lpthread
CFLAGS := -O3 -Wall -std=c99  -pthread 
LDFLAGS := -s -L. -lsem -lshmem -lpthread -lrt

.PHONY: all clean

all: libsem.a libshmem.so main.x producer.x consumer.x $(EXEC1) $(EXEC2)

libsem.a: sem.o
sem.o: sem.c

libshmem.so: shmem.o
shmem.o: shmem.c

$(NAME).x: $(NAME).o 
$(NAME).o: $(NAME).c sem.c shmem.c

main.x: main.o circbuf.o
main.o: main.c sem.c shmem.c
circbuf.o: circbuf.c circbuf.h

producer.x: producer.o circbuf.o
producer.o: producer.c sem.c shmem.c

consumer.x: consumer.o circbuf.o
consumer.o: consumer.c sem.c shmem.c

$(EXEC1): $(OBJ)
	$(CC) $^ -o $@ -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC2): $(OBJ)
	$(CC) $^ -o $@ -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

libshmem.so:
	$(CC) -shared $^ -o $@

shmem.o:
	$(CC) -c -O -fPIC shmem.c

libsem.a: sem.o
	ar rv $@ $<

%.x: %.o
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.[aox])
