#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>
#define PRIORITY 0


typedef char komunikat;

mqd_t msgCreate(const char* name){
    mqd_t temp;
    if ( (temp=mq_open(name, O_CREAT | O_RDWR, S_IRWXU, NULL)) == -1){
        perror("Blad tworzenia obiektu kolejki: ");
        exit(EXIT_FAILURE);
    }
    printf("poprawnie stworzono obiekt kolejki\n");
    return temp;
}

mqd_t msgOpen(const char* name){
    mqd_t temp;
    if ( (temp=mq_open(name, O_RDWR)) == -1){
        perror("Blad otwierania obiektu kolejki: ");
        exit(EXIT_FAILURE);
    }
    printf("poprawnie otworzono obiekt kolejki\n");
    return temp;
}

void msgClose(mqd_t fd){
    if (mq_close(fd) == -1){
        perror("Blad zamkniecia obiektu kolejki: ");
        exit(EXIT_FAILURE);
    }
    printf("Pomyslnie zamknieto obiekt kolejki\n");
}

void msgRm(const char *name){
    if (mq_unlink(name) == -1){
        perror("Blad zamkniecia obiektu kolejki: ");
        exit(EXIT_FAILURE);
    }
    printf("Pomyslnie usunieto obiekt kolejki\n");
}

void msgSend(int msgid, komunikat* msg){
    if (mq_send(msgid, msg, strlen(msg), PRIORITY) == -1){
        perror("Nie udalo sie wyslac wiadomosci do kolejki: ");
        exit(EXIT_FAILURE);
    }
    printf("Pomyslnie wyslano wiadomosc do kolejki\n");
}

void msgRecv(int msgid, komunikat *msg){
    struct mq_attr attr;

    if (mq_getattr(msgid, &attr) == -1){
        perror("Blad wydobycia szczegolow");
        exit(EXIT_FAILURE);
    }

    if (mq_receive(msgid, msg, attr.mq_msgsize, PRIORITY) == -1){
        perror("Blad odbioru wiadomosci z kolejki: ");
        exit(EXIT_FAILURE);
    }
    printf("Pomyslnie odebrano wiadomosc\n");
}

void msgInfo(int msgid){
    struct mq_attr attr;
    if (mq_getattr(msgid, &attr) == -1){
        perror("Blad wydobycia szczegolow");
        exit(EXIT_FAILURE);
    }
    printf("Maksymalna ilosc wiadomosci w kolejce: %ld\n", attr.mq_maxmsg);
    printf("Maksymalny rozmiar wiadomosci: %ld\n", attr.mq_msgsize);
    printf("Liczba wiadomosci bedacych obecnie w kolejce: %ld\n\n", attr.mq_curmsgs);
}