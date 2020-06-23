#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "sem.h"
#include "procinfo.h"
#define N 10
#define SIZE 10

int openFile(char* path){
    int code;
    if ( (code=open(path, O_RDWR)) == -1 ){
        perror("Opening error");
        exit(EXIT_FAILURE);
    }
    return code;
}

char* readFromFile(char* path){
    int open_code = open(path, O_RDONLY);
    int read_code;
    int i=0;

    char* text = malloc(SIZE * sizeof(char));
    char* letter = malloc(sizeof(char));

    if ( (text==NULL) || (letter==NULL) ) { perror("Memory problems: "); exit(EXIT_FAILURE); }

    while((read_code=read(open_code, letter, 1)) > 0){
        text[i] = *letter;
        i++;
    }
    free(letter);
    close(open_code);
    return text;
}

int writeToFile(char* message, int code){
    int write_code;
    if( (write_code=write(code, message, strlen(message))) == -1){
        perror("Writing error");
        exit(EXIT_FAILURE);
    }
    return write_code;
}

int main(int argc, char* argv[]){
    int     open_code;      //numer.txt descriptor
    int     numer;          //Variable storing number read from numer.txt
    char*   bufor;          //Buffer to which content of file is written
    semid   semafor;        //Descriptor of semaphore

    procinfo(argv[0]);
    semafor = semOpen(argv[1]);
    
    
    for (int i=0; i<N; i++){
        open_code = openFile("numer.txt");
        
        semInfo(semafor);
        semP(semafor);

        //BEGINING OF CRITICAL SECTION
        printf("Critiacl section n %d of pid=%d process\n", i, getpid());
        
        bufor = readFromFile("numer.txt");
        numer = atoi(bufor);
        char *msg = malloc((strlen(bufor)+1)*sizeof(char));
        sprintf(msg, "%d", numer+1);
        writeToFile(msg, open_code);

        free(bufor);
        free(msg);
        
        semInfo(semafor);

        //END OF CRITICAL SECTION
        semV(semafor);
        semInfo(semafor);
        close(open_code);
    }
    
    
    return 0;
}