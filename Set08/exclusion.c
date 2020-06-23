#define _GNU_SOURCE
#define _REENTRANT
#include <stdio.h>      //printf, perror
#include <stdlib.h>     //EXIT_FAILURE
#include <unistd.h>     //sleep
#include <pthread.h>    //threads and mutexes
#include <errno.h>      //errno variable
#define N 10
#define K 10


int global_counter = 0;
pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;


void *thread(void *number){
    
    int private_counter;
    long position = (long) number;

    
    for (int i=0; i < K; i++){
        printf("\033[%ld;%dH\033[32m\033[2Kthread %ld  : PRIVATE SECTION\n", position, 0,position);
        
        if ( (errno=pthread_mutex_lock(&locker)) ) { 
            perror("Lock error: "); 
            exit(EXIT_FAILURE); 
        }

        printf("\033[%ld;%dH\033[31m\033[2Kthread %ld  : CRITICAL SECTION\n", position, 52, position);

        private_counter = global_counter;
        private_counter++;
        usleep(90000);
        global_counter = private_counter;

        if ( (errno = pthread_mutex_unlock(&locker)) ) { 
            perror("Unlock error: "); 
            exit(EXIT_FAILURE); 
        }

        printf("\033[%ld;%dH\033[32m\033[2Kthread %ld  : PRIVATE SECTION\n", position, 0, position);
        usleep(90000);
    }
    
    return NULL;
}


int main(int argc, char* argv[]){
    if( system("clear") != 0 ) perror("clear");
    pthread_t tablica_watkow[N];

    for (long i=0; i < N; ++i){
        if ( (errno = pthread_create(&tablica_watkow[i], NULL, thread, (void *) (i+1) ) ) ) { 
            perror("Erro creating thread: "); 
            exit(EXIT_FAILURE); 
        }
    }


    for (long i=0; i < N; ++i){
        if ( (errno = pthread_join(tablica_watkow[i], NULL)) ) { 
            perror("Joining failed: "); 
            exit(EXIT_FAILURE); 
        }
    }

    printf("\033[%d;%dH\033[0m\033[2K", N+1, 0);
    printf("\033[%d;1HCorrect counter value: %d, effective value: %d\n", N*K+1, N*K, global_counter);
    return 0;
}