#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>
#define PRIORITY 0


typedef char information;

mqd_t msgCreate(const char* name, int mode){
    mqd_t temp;
    if ( (temp=mq_open(name, O_CREAT | mode, S_IRWXU, NULL)) == -1){
        perror("Creating message queue failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly created %s message queue\n", name);
    return temp;
}

mqd_t msgOpen(const char* name, int mode){
    mqd_t temp;
    errno=0;
    if ( (temp=mq_open(name, mode)) == -1){
        if (errno == ENOENT){
            printf("Such an object doesn't exists. It is going to be created now.\n");
            return msgCreate(name, mode);
        }
        perror("Opening queue failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly opened %s queue\n", name);
    return temp;
}

void msgClose(mqd_t fd){
    if (mq_close(fd) == -1){
        perror("Closing queue failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly closed queue\n");
}

void msgRm(const char *name){
    if (mq_unlink(name) == -1){
        perror("Removing queue failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly removed queue\n");
}

void msgSend(int msgid, information* msg){
    if (mq_send(msgid, msg, strlen(msg), PRIORITY) == -1){
        perror("Couldn't send message to queue: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly sent message: %s\n", msg);
}

void msgRecv(int msgid, information *msg, char *name){
    struct mq_attr attr;
    errno = 0;
    if (mq_getattr(msgid, &attr) == -1){
        perror("Error getting attributes");
        exit(EXIT_FAILURE);
    }

    if (mq_receive(msgid, msg, attr.mq_msgsize, PRIORITY) == -1){
        if (errno == EINTR){
            printf("CTRL+C was used, process will be finished!\n");
            printf("Closing and deleting queues\n");
            msgClose(msgid);
            msgRm(name);
            exit(EXIT_SUCCESS);
        }
        perror("Receiving message failed: ");
        exit(EXIT_FAILURE);
    }
    printf("Correctly received message: %s\n", msg);
}

void msgInfo(int msgid){
    struct mq_attr attr;
    if (mq_getattr(msgid, &attr) == -1){
        perror("Getting attributes failed");
        exit(EXIT_FAILURE);
    }
    printf("Maximal number of messages in queue: %ld\n", attr.mq_maxmsg);
    printf("Maximal size of one message: %ld\n", attr.mq_msgsize);
    printf("Number of messages in queue: %ld\n\n", attr.mq_curmsgs);
}