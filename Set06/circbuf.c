#include <stdio.h>
#define SIZE_OF_BUFFER 8


typedef char goods;

typedef struct cykl{
    int     bufferLength;
    int     readIndex;
    int     writeIndex;
    goods   buffer[SIZE_OF_BUFFER];
}Circular;

int isBufferFull(Circular* buffer){
    return (buffer->bufferLength == SIZE_OF_BUFFER);
}

int isBufferEmpty(Circular* buffer){
    return (buffer->bufferLength == 0);
}

void writeChar(Circular* buffer, goods value){
    if (buffer->writeIndex != SIZE_OF_BUFFER){
        buffer->buffer[buffer->writeIndex] = value;
        buffer->writeIndex++;
        if (buffer->writeIndex == SIZE_OF_BUFFER) buffer->writeIndex=0;
        buffer->bufferLength++;
    }
    else{
        buffer->writeIndex=0;
        writeChar(buffer, value);
    }
}

goods readChar(Circular *buffer){
    goods temp;

    if (buffer->readIndex == SIZE_OF_BUFFER){
        buffer->readIndex = 0;
    }
    
    temp = buffer->buffer[buffer->readIndex];
    buffer->buffer[buffer->readIndex] = 0;
    buffer->readIndex++;
    buffer->bufferLength--;
    return temp;
}


void printInfo(Circular* buffer){
    printf("bufferLength = %d\n", buffer->bufferLength);
    printf("readIndex = %d\n", buffer->readIndex);
    printf("writeIndex = %d\n", buffer->writeIndex);
}