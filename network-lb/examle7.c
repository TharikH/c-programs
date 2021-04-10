#include<unistd.h>
#include<stdio.h>

void main(){
    if(fork() && fork()){
        
        fork();
        printf("inside\n");
        fork();
        
    }
    printf("outside\n");
}