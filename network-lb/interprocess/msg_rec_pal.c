#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct buf{
    long type;
    char msg[100];
};

int isPallindrome(char *str){
    int last=strlen(str)-1,first=0;
    while(first<last){
        if(str[first++] != str[last--]){
            return 0;
        }
    }
    return 1;
}
void main(){
    struct buf message;
    key_t key;
    int msgid;

    key=ftok("msg_send_pal.c",5);

    msgid=msgget(123456,0666 | IPC_CREAT);

    msgrcv(msgid,message.msg,sizeof(message.msg),1,0);

    printf("Data recieved :%s\n",message.msg);
    if(isPallindrome(message.msg)){
        printf("It is Pallindrome\n");
    }else{
        printf("It is not Pallindrome\n");
    }
    msgctl(msgid, IPC_RMID, NULL);
}