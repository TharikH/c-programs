#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

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
    message.type=1;

    printf("enter string : ");
    scanf("%s",message.msg);

    msgsnd(msgid,&message,sizeof(message),0);

    printf("Data send \n");
}
