#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <sys/shm.h>
#include<string.h>

#define MAX 10
struct student{
    char name[30];
    int mark;
};
void sortClass(struct student *class,int roll){
    int flag=0;
    struct student temp;
    for(int i=0;i<roll-1;i++){
        for(int j=i;j<roll;j++){
            if(class[i].mark < class[j].mark){
                memcpy(&temp,&class[i],sizeof(struct student));
                memcpy(&class[i],&class[j],sizeof(struct student));
                memcpy(&class[j],&temp,sizeof(struct student));
            }
        }
    }

}
void display(struct student *class,int roll){
    printf("Rank list is :\n ");
    for (int i = 0; i < roll; i++)
    {
        printf("%d)%s\n ",i+1,class[i].name);
    }
}

void main(){
    struct student *memory,class[MAX],*temp;

    key_t key;
    int shmid,roll=0;

    key=ftok("student.c",50);
    shmid = shmget(key, sizeof(struct student)*MAX, 0666|IPC_CREAT);

    if(shmid == -1){
        printf("error");
        exit(0);
    }
    memory=(struct student *)shmat(shmid,NULL,0);
    temp=memory;
    while(temp->mark != -1){
        roll++;
        temp++;
    }
    memcpy(class,memory,sizeof(struct student)*roll);
    sortClass(class,roll);
    display(class,roll);
    // printf("name is :%s %d %d",memory->name,memory->mark,roll);
    shmdt(memory);
    shmctl(shmid,IPC_RMID,NULL);

}
