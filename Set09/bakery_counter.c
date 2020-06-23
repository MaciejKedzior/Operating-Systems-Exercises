#define _REENTRANT
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#define N 3
#define K 10000


volatile bool   choosing[N];
volatile int    number[N];
volatile int    global_counter=0;


int max(volatile int array[]){
    int maximum = array[0];
    for(int i=1; i<N; i++) if (array[i] > maximum) maximum = array[i];
    return maximum;
}

void lock(int i){
    choosing[i] = true;
    number[i] = max(number)+1;
    choosing[i] = false;
    for (int j=0; j < N; j++){
        while (choosing[j]);
        while ( number[j] != 0 && ( (number[j] < number[i]) || ((number[j] == number[i]) && (j<i) )));
    }  
}

void unlock(int i){
    number[i]=0;
}


void *thread(void *value){
    
    //long position = (long) value+1;
    int  private;
    
    for (int i=0; i < K; i++){
        //printf("\033[%ld;%dH\033[32m\033[2KTHREAD %ld  : PRIVATE SECTION\n", position, 0,position);

        //printf("\033[%ld;%dH\033[31m\033[2KTHREAD %ld  : CRITICAL SECTION\n", position, 52, position);
        
        private = global_counter;
        private++;
        global_counter=private;

        //printf("\033[%ld;%dH\033[32m\033[2Kthread %ld  : SEKCJA PRYWATNA\n", position, 0, position);
    }
    
    return NULL;
}


int main (void){
    if( system("clear") != 0 ) perror("clear");
    pthread_t   threads[N];

    for (int i=0; i<N; i++) choosing[i] = false;
    for (int i=0; i<N; i++) number[i] = 0;

    for (long i=0; i<N; i++) pthread_create(&threads[i], NULL, thread, (void *) i);
    for (int i=0; i<N; i++) pthread_join(threads[i], NULL);

    printf("\033[%d;%dH\033[0m\033[2K", N+1, 0);
    printf("\033[%d;1HCorrect counter value: %d, effective value: %d\n", N*K+1, N*K, global_counter);

    return 0;
}
