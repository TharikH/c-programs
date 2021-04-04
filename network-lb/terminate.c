#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    if(fork() == 0){
        sleep(4);
        printf("inside 1st child\n");
    }else{
        if(fork() == 0){
            sleep(2);
            printf("inside 2nd child\n");
        }else{
            if(fork() == 0){
                printf("inside 3rd child\n");
            }else{
                sleep(7);
                printf("parent\n");
            }
        }
    }
    return 0;
}