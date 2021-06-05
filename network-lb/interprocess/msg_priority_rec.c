#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct buf{
    long type;
    char msg[100];
};
void main(){
    struct buf message;
    key_t key;
    int msgid;

    key=ftok("msg_send_pal.c",5);

    msgid=msgget(key,0666 | IPC_CREAT);

    

    msgrcv(msgid,&message,sizeof(message),1,1);
    printf("Data recieved :%s\n",message.msg);
    msgrcv(msgid,&message,sizeof(message),1,2);
    printf("Data recieved :%s\n",message.msg);

    msgctl(msgid, IPC_RMID, NULL);
}