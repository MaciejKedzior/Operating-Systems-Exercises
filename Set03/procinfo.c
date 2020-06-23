#define _XOPEN_SOURCE 500
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int procinfo(const char* name){
    printf("Process name: %s, UID: %d, GID: %d, PID: %d, PPID: %d, PGRP: %d, PGID: %d\n", 
            name, getuid(), getgid(), getpid(), getppid(), getpgrp(), getpgid(getpid()));
    return 0;
}
