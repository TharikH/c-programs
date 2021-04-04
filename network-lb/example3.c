#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
   if(fork()==0)
       printf("hello from child\n");
   else
       printf("parent\n");
   return 0;
}