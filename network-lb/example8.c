#include<stdio.h>
#include<unistd.h>

void main(){
    if(fork() && (!fork())){
        if(fork() || fork()){
            fork();
        }
    }
    printf("2 ");
}