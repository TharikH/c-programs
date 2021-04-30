#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

#define MAX 5

int arr[MAX],in=0,out=0;
sem_t empty,full,sem;
// pthread_mutex_t sem;
void producer(int val){
    sem_wait(&empty);
    sem_wait(&sem);
    // pthread_mutex_lock(&sem);
    arr[in]=val;
    printf("producer producing :%d \n",arr[in]);
    in=(in + 1)%MAX;
    sem_post(&sem);
    // pthread_mutex_unlock(&sem);
    sem_post(&full);
}
void consumer(){
    sem_wait(&full);
    sem_wait(&sem);
    // pthread_mutex_lock(&sem);
    printf("consumer consuming :%d \n",arr[out]);
    out=(out + 1)%MAX;
    sem_post(&sem);
    // pthread_mutex_unlock(&sem);
    sem_post(&empty);
}
void *producerLoop(void *temp){
    for (int i = 1; i < 8; i++)
    {   
        producer(i);
    }
    return NULL;
}
void *consumerLoop(void *temp){
    for (int i = 1; i < 8; i++)
    {
        consumer();
    }
    return NULL;
}
void main(){
    pthread_t prod,cons;
    sem_init(&empty,0,MAX-1);
    sem_init(&full,0,0);
    sem_init(&sem,0,1);
    pthread_create(&prod,NULL,producerLoop,NULL);
    pthread_create(&cons,NULL,consumerLoop,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
}
