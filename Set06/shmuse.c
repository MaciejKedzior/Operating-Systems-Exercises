#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shmem.h"
#define N 10

int main(int argc, char* argv[]){
    char*   shared_memory_name="/buffer";
    char    argument, buffer[BUFSIZ];
    void*   shared_memory_object;
    int     size=N, open_code, read_code;    


    if (argc > 3){
        printf("Improper cmd args amount\n");
        exit(EXIT_FAILURE);
    }

    if (argc==1){
        printf("shmuse.x executed without any cmd arguments!\n");
        exit(EXIT_SUCCESS);
    }

    if (argc == 2) argument = argv[1][0];
    else if (argc == 3){
        argument = argv[1][0];
        size = atoi(argv[2]);
    }
    else argument = 'x';

    switch (argument){
        case 'c':
            printf("Option c - creating segment\n");
            shmCreate(shared_memory_name, size);
            exit(EXIT_SUCCESS);

        case 'd':
            printf("Option d - deleting segment\n");
            shmRm(shared_memory_name);
            exit(EXIT_SUCCESS);

        case 'r':
            printf("Option r - reading content of segment\n");
            open_code = shmOpen(shared_memory_name);

            printf("Content of shared memory: \n");
            while ((read_code=read(open_code, buffer, BUFSIZ)) > 0){
                if(write(STDOUT_FILENO, buffer, read_code)==-1){
                    perror("Write error: ");
                    exit(EXIT_FAILURE);
                }
            }

            printf("\n");
            exit(EXIT_SUCCESS);

        case 'w':
            printf("Option w -writing to shared memory\n");
            open_code = shmOpen(shared_memory_name);
            if ((read_code=read(STDIN_FILENO, buffer, BUFSIZ)) == -1){
                perror("Read error: ");
                exit(EXIT_FAILURE);
            }
            printf("Written %d bytes of data from file\n", read_code);

            if (read_code != shmSize(open_code)){
                printf("Size of segment will be changed\n");
                open_code = shmCreate(shared_memory_name, read_code);
            }

            shared_memory_object = (char*) shmMap(open_code, read_code);
            memset(shared_memory_object, 0, shmSize(open_code));
            memcpy(shared_memory_object, buffer, read_code);
            
            printf("Correctly added data to object\n");
            exit(EXIT_SUCCESS);

        case 'i':
            printf("Option i - shared memory object info\n");
            open_code = shmOpen(shared_memory_name);
            printf("Memory size: %d\n", shmSize(open_code));
            shmInfo(open_code);
            exit(EXIT_SUCCESS);

        default:
            printf("Given argument is not proper, here are legal ones: \n");
            printf("c <size> , where size>0 - creating size-length shared memory object\n");
            printf("d - deleting shared memory segment\n");
            printf("r - reading content of shared memory object\n");
            printf("w < \"nazwa_pliku\" - writing from file to shared memory object\n");
            printf("i - shared memory object info\n");
            exit(EXIT_FAILURE);
    }
    return 0;
}