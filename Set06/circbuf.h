#ifndef CIRCBUF_h
#define CIRCBUF_H
#define N 10

typedef char goods;

typedef struct cykl{
    int     bufferLength;
    int     readIndex;
    int     writeIndex;
    goods   buffer[N];
}Circular;

int isBufferFull(Circular*);
int isBufferEmpty(Circular* buffer);
void writeChar(Circular* buffer, goods value);
goods readChar(Circular *buffer);
void initializeBuffer(Circular* buffer);
void printInfo(Circular* buffer);

#endif