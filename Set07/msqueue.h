#ifndef MSQ_H
#define MSQ_h
#include <mqueue.h>
#define QUEUE_NAME "/queue"

typedef char information;

mqd_t msgCreate(const char* name, int mode);
mqd_t msgOpen(const char* name, int mode);
void msgClose(mqd_t fd);
void msgRm(const char *name);
void msgSend(int msgid, information* msg);
void msgRecv(int msgid, information *msg, char *name);
void msgInfo(int msgid);

#endif