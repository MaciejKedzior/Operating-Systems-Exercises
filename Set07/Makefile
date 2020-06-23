CC := gcc
LIB_NAME := msqueue
LIB_DIR := .
LDLIBS := -lrt
CFLAGS := -O3 -Wall -std=c99 
LDFLAGS := -s -L. -lmsqueue -lrt

.PHONY: all clean


all: libmsqueue.so libmsg.so libmsg.a client.x server.x 

serclient.o: serclient.c

libmsqueue.so: msqueue.o
libmsqueue.o: msqueue.c

client.x: client.o serclient.o
client.o: client.c msqueue.h

server.x: server.o serclient.o
server.o: server.c msqueue.h

libmsg.so: msg.o
msg.o: msg.c

libmsg.so:
	$(CC) -shared $^ -o $@

libmsqueue.so:
	$(CC) -shared $^ -o $@

msqueue.o:
	$(CC) -c -O msqueue.c

libmsg.a: msg.o
	ar rv $@ $<

%.x: %.o
	$(CC) $^ -o $@ -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<


clean:
	$(RM) $(wildcard *.[aox])
