#define _POSIX_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "procinfo.h"
#include <sys/wait.h>

int main(int argc, char* argv[]){
    //sprawdzenie poprawnej ilości argumentów
    if (argc != 3) { printf("Nieodpowiednia liczba argumentow!\n"); exit(EXIT_FAILURE); }
    int pid;
    int sig_number = atoi(argv[2]);
    procinfo(argv[0]);

    switch (pid=fork()){
        //błąd przy powstaniu dziecka
        case -1:
            perror("Blad forkowania!\n");
            exit(EXIT_FAILURE);
        //dziecko
        case 0:
            execl("./obsluga.x", "obsluga.x", argv[1], argv[2], NULL);
        //rodzic
        default:
            //sprawdzenie, czy proces potomny istnieje
            if ((kill(pid, 0)) == -1) { perror("Nie mozna wyslac sygnalu!\n"); exit(EXIT_FAILURE); }

            sleep(1);
            //wysyłanie sygnałów do procesu potomnego, w wypadku błędu wyjście z programu
            if((kill(pid, sig_number))==-1) { printf("blad wysylania!\n"); exit(EXIT_FAILURE); }
            else { wait(NULL); exit(EXIT_SUCCESS); }
    }
    return 0;
}