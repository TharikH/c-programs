#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<pthread.h>
#include <fcntl.h>
#include<unistd.h>

int readcount=0;
#define MAX 10
struct semdetails{
    sem_t *writer,*mutex;
    pid_t id;
};
void *readerfun(void * args){
    struct semdetails *details=(struct semdetails *)args;
    sem_t *writer=details->writer,*mutex=details->mutex;
    sem_wait(mutex);
    readcount++;
    if(readcount == 1){
        sem_wait(writer);
    }
    sem_post(mutex);

    key_t key = ftok("reader.c",5);
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    
    int *num = (int*) shmat(shmid,(void*)0,0);
    printf("Data read by %d is : %d\n",details->id,*num);
    shmdt(num);


    sem_wait(mutex);
    readcount--;
    if(readcount == 0){
        sem_post(writer);
    }
    sem_post(mutex);

}
void main(){
    sem_t *writer,*mutex;
    const char *writer_name="writer";
    const char *mutex_name="mutex";
    pthread_t readers[MAX];
    struct semdetails detail[MAX];

    writer = sem_open(writer_name,O_CREAT,0666,1);
    mutex = sem_open(mutex_name,O_CREAT,0666,1);

    for (int i = 0; i < MAX; i++)
    {
        detail[i].writer=writer;
        detail[i].mutex=mutex;
        detail[i].id=i;
        pthread_create(&readers[i],NULL,readerfun,(void *)&detail[i]);
    }
    for (int i = 0; i < MAX; i++)
    {
        pthread_join(readers[i],NULL);
    }
    
    sem_close(writer);sem_close(mutex);
    sem_unlink(writer_name);sem_unlink(mutex_name);

    key_t key = ftok("reader.c",5);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    shmctl(shmid,IPC_RMID,NULL);


}