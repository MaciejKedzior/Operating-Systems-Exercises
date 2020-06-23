#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define N 1000

char buf[N];
void consumer(int pipe_name, int file_descr){
    while (read(pipe_name, buf, 1) > 0){
        if(write(STDOUT_FILENO, "[Obtaining]: ", sizeof("[Obtaining]: "))==-1) {perror(""); exit(EXIT_FAILURE);}
        if(write(STDOUT_FILENO, buf, 1)==-1) {perror(""); exit(EXIT_FAILURE);}
        if(write(STDOUT_FILENO, "\n", 1)==-1) {perror(""); exit(EXIT_FAILURE);}
        if(write(file_descr, buf, 1)==-1) {perror("Consumer error:"); exit(EXIT_FAILURE);}
        usleep(100000);
    }
}

int main(int argc, char* argv[]){
    int pipe_read, storage;
    if (
        ( (pipe_read = open(argv[1], O_RDONLY)) == -1 )
            ||
        ( (storage = open("storage.txt", O_RDWR | O_CREAT | O_APPEND, S_IRWXU)) == -1 )
    ) {
        perror("Open error!");
        exit(EXIT_FAILURE);
    }
    else
        printf("File opened properly! pipe_read=%d\tstorage=%d\n", pipe_read, storage);
    
    consumer(pipe_read, storage);
    close(storage);
    close(pipe_read);
    return 0;
}
