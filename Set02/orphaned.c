#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procinfo.h"


int main(int argc, char* argv[]){
    procinfo(argv[0]);
    pid_t pid = fork();
    if (pid==-1) { perror("FORK ERROR!\n"); exit(1); }
    if (pid==0) { 
        sleep(5); 
        procinfo(argv[0]); 
        printf("status: %d\n", system("pstree -p"));
    }
    
    return 0;
}
