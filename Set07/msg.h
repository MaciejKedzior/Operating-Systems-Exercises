#ifndef MSQ_H
#define MSQ_h
#include <mqueue.h>

typedef char komunikat;

mqd_t msgCreate(const char* name);
mqd_t msgOpen(const char* name);
void msgClose(mqd_t fd);
void msgRm(const char *name);
void msgSend(int msgid, komunikat* msg);
void msgRecv(int msgid, komunikat *msg);
void msgInfo(int msgid);

#endif