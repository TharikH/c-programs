#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int n=5,k=0;
    if(fork() == 0){
        for(int i=0;i<n;i+=2){
            printf("%d ",i);
            if(k){
                k=0;
                sleep(2);
                }
            else{
                k=1;
                sleep(1);
            }
        }
    }else{
        ++n;
        for(int i=1;i<n;i+=2){
            printf("%d ",i);
            if(!k){
                k=1;
                sleep(2);
                }
            else{
                k=0;
                sleep(1);
            }
        }
    }
}