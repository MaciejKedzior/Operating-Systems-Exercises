#include <stdio.h>          //printf
#include <stdlib.h>         //EXIT_FAILURE
#include <sys/types.h>      //fork
#include <unistd.h>         //fork
#include <sys/wait.h>       //wait
#include <signal.h>
#include "shmem.h"          //functions which handle shared memory
#include "sem.h"            //functions which handle posix semaphores
#include "circbuf.h"        //cyclical buffer and its handling


int main(int argc, char* argv[]){
    pid_t       producer, consumer;
    int         file_descr;
    semid       prod_semaphore, cons_semaphore;
    char        shared_mem_name[]="/bufor", prod_sem_name[]="/prod_sem", cons_sem_name[]="/cons_sem";
    Circular*   shared_mem_object;

    prod_semaphore = semCreate(prod_sem_name, N);
    cons_semaphore = semCreate(cons_sem_name, 0);
    
    file_descr = shmCreate(shared_mem_name, sizeof(Circular));
    shared_mem_object = shmMap(file_descr, sizeof(Circular));
    

    producer = fork();
    if (producer == -1){ perror("Producer fork error: "); exit(EXIT_FAILURE); }
    else if (producer == 0) 
        execl("./producer.x", "producer.x", shared_mem_name, prod_sem_name, cons_sem_name ,NULL); 
    else{
        consumer = fork();
        if (consumer == -1){ perror("Consumer fork error: "); exit(EXIT_FAILURE); }
        else if (consumer == 0) 
            execl("./consumer.x", "consumer.x", shared_mem_name, prod_sem_name, cons_sem_name, NULL);
        else{
            signal(SIGTERM, SIG_IGN);
            wait(NULL);
            wait(NULL);
            
            if (system("diff -s warehouse.txt storage.txt") == -1){
                perror("Error while using diff: ");
                exit(EXIT_FAILURE);
            }
            
            semClose(prod_semaphore); semRemove(prod_sem_name);
            semClose(cons_semaphore); semRemove(cons_sem_name);
            shmClose(shared_mem_object, file_descr, sizeof(Circular));
            shmRm(shared_mem_name);
        }
    }

    return 0;
}
