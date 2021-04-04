#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

int fact(int n){
    int fac=1;
    while (n)
    {
        fac*=n;
        --n;
    }
    return fac;
}
int main(int argc,char*argv[]){
    int limit=atoi(argv[1]);
    if(fork() == 0){
        for (int i = 1; i <= limit; i++)
        {
            printf("%d ",fact(i));
        }
        printf("\n");
    }else{
        wait(NULL);
    }
    return 0;
}