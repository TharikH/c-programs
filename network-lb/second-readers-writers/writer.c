#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<pthread.h>
#include <fcntl.h>
#include<unistd.h>

int writecount=0;
#define MAX 10
struct semdetails{
    sem_t *writer,*mutex,*reader;
    pid_t id;
};
void *readerfun(void * args){
    struct semdetails *details=(struct semdetails *)args;
    sem_t *writer=details->writer,*mutex=details->mutex,*reader=details->reader;

    sem_wait(mutex);
    writecount++;
    if(writecount == 1){
        sem_wait(reader);
    }
    sem_post(mutex);
    sem_wait(writer);

    key_t key = ftok("reader.c",5);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    int *num = (int*) shmat(shmid,(void*)0,0);
    (*num)++;
    printf("Data written by %d is : %d\n",details->id,*num);
    shmdt(num);

    sem_post(writer);
    sem_wait(mutex);
    writecount--;
    if(writecount == 0){
        sem_post(reader);
    }
    sem_post(mutex);

}
void main(){
    sem_t *writer,*mutex,*reader;
    const char *writer_name="writer2";
    const char *mutex_name="mutex2";
    const char *reader_name="reader2";
    pthread_t writers[MAX];
    struct semdetails detail[MAX];

    writer = sem_open(writer_name,O_CREAT,0666,1);
    mutex = sem_open(mutex_name,O_CREAT,0666,1);
    reader = sem_open(reader_name,O_CREAT,0666,1);

    for (int i = 0; i < MAX; i++)
    {
        detail[i].writer=writer;
        detail[i].mutex=mutex;
        detail[i].reader=reader;
        detail[i].id=i;
        pthread_create(&writers[i],NULL,readerfun,(void *)&detail[i]);
    }
    for (int i = 0; i < MAX; i++)
    {
        pthread_join(writers[i],NULL);
    }
    
    sem_close(writer);sem_close(mutex);sem_close(reader);
    sem_unlink(writer_name);sem_unlink(mutex_name);sem_unlink(reader_name);


}