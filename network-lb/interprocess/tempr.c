#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct buf{
    long type;
    char msg[100];
};

void main(){
    struct buf msg1,msg2,msg3;
    key_t key;
    int msgid;
    key=ftok("temp.c",5);

    msgid=msgget(key,0666 | IPC_CREAT);

    msgrcv(msgid,&msg1,sizeof(struct buf),3,0);
    printf("Data recieved :%s\n",msg1.msg);

    msgrcv(msgid,&msg2,sizeof(struct buf),2,0);
    printf("Data recieved :%s\n",msg2.msg);

    msgrcv(msgid,&msg3,sizeof(struct buf),1,0);
    printf("Data recieved :%s\n",msg3.msg);
    
    msgctl(msgid, IPC_RMID, NULL);
}
