#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define MAX 5

int arr[MAX],sem=1,full=0,empty=MAX;

void signal(int *s){
    (*s)++;
}
void wait(int *s){
    while(*s <= 0);
    (*s)--;
}

void producer(int val){
    wait(&empty);
    wait(&sem);
    arr[full]=val;
    // printf("%d ",arr[full]);
    signal(&sem);
    signal(&full);
}
void consumer(){
    wait(&full);
    wait(&sem);
    printf("%d ",arr[full - 1]);
    signal(&sem);
    signal(&empty);
}
void *producerLoop(void *temp){
    printf("hell");
    for (int i = 0; i < 8; i++)
    {   
        producer(i);
    }
    return NULL;
}
void *consumerLoop(void *temp){
    printf("hell000");
    for (int i = 0; i < 8; i++)
    {
        consumer();
    }
    return NULL;
}
void main(){
    pthread_t prod,cons;
    printf(" 000 ");
    pthread_create(&prod,NULL,producerLoop,NULL);
    pthread_create(&cons,NULL,consumerLoop,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
}