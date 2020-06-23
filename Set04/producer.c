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
void producer(int pipe_name, int file_descr){
    while (read(file_descr, buf, 1) > 0){
        if(write(STDOUT_FILENO, "[Sending]: ", sizeof("[Sending]: ")) == -1) {
            perror(""); 
            exit(EXIT_FAILURE);
        }

        if(write(STDOUT_FILENO, buf, 1)==-1) {
            perror(""); 
            exit(EXIT_FAILURE);
        }

        if(write(STDOUT_FILENO, "\n", 1)==-1) {
            perror(""); 
            exit(EXIT_FAILURE);
        }

        if((write(pipe_name, buf, 1)==-1)) {
            perror("Producer error: "); 
            exit(EXIT_FAILURE);
        }
        usleep(100000);
    }
}

int main(int argc, char* argv[]){
    int pipe_read, warehouse;
    if (
        ( (pipe_read = open(argv[1], O_WRONLY)) == -1 )
            ||
        ( (warehouse = open("warehouse.txt", O_RDONLY)) == -1 )
    ) {
        perror("Opening error!");
        exit(EXIT_FAILURE);
    }
    else
        printf("File opened properly! pipe_read=%d\twarehouse=%d\n", pipe_read, warehouse);
    
    producer(pipe_read, warehouse);
    close(warehouse);
    close(pipe_read);
    return 0;
}