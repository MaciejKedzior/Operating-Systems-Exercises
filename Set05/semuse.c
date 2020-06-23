#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"


int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Niepoprawna ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    char* name="/semafor";
    char argument = argv[1][0];
    semid semafor;

    if (argument == 'i'){
        semafor = semCreate(name, 1);
        semInfo(semafor);
        exit(EXIT_SUCCESS);
    }
    else semafor = semOpen(name);
    
    if (argument =='r'){
        semRemove(name);
        exit(EXIT_SUCCESS);
    }
    else if (argument == 'p'){
        semP(semafor);
        semInfo(semafor);
        exit(EXIT_SUCCESS);
    }
    else if (argument == 'v'){
        semV(semafor);
        semInfo(semafor);
        exit(EXIT_SUCCESS);    
    }
    else if (argument == 'q'){
        semInfo(semafor);
        exit(EXIT_SUCCESS);        
    }
    else{
        printf("Niepoprawny argument\n");
        exit(EXIT_FAILURE);        
    }

    return 0;
}