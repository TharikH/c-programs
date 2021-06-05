#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <sys/shm.h>
#include<string.h>

#define MAX 3
struct student{
    char name[30];
    int mark;
};

void main(){
    struct student class[3],*memory;
    strcpy(class[0].name,"ramu");
    strcpy(class[1].name,"sonu");
    strcpy(class[2].name,"monu");

    class[0].mark=100;
    class[1].mark=45;
    class[2].mark=67;

    key_t key;
    int shmid;

    key=ftok("student.c",5);
    shmid = shmget(key, sizeof(struct student)*MAX, 0666|IPC_CREAT);

    if(shmid == -1){
        printf("error");
        exit(0);
    }
    memory=(struct student *)shmat(shmid,NULL,0);
    // memcpy(memory,class,sizeof(struct student)*MAX);
    memory=class;
    shmdt(memory);

}