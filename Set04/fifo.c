#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
    int producer, consumer;
    char* pipe = "pipe";

    if (mkfifo(pipe, 0666) == -1){   //Creating named pipe
        perror("Named pipe error!\n");
        exit(EXIT_FAILURE);
    }   
    
    producer=fork();                   // Creating and executing producer program
    if (producer == -1) { 
        perror("FORK ERROR!"); 
        exit(EXIT_FAILURE); 
    }
    else if (producer == 0) execl("./producer.x", "producer.x", pipe, NULL);
    else{
        consumer=fork();                   // Creating and executing consumer program
        if (consumer==-1) { 
            perror("FORK ERROR!\n"); 
            exit(EXIT_FAILURE); 
        }
        else if(consumer==0) execl("./consumer.x", "consumer.x", pipe, NULL);
        else{
            wait(NULL);
            wait(NULL);
            if(system("diff -s warehouse.txt storage.txt")==-1) {perror(""); exit(EXIT_FAILURE);}
            unlink(pipe);
        }
    }
    
    return 0;
}