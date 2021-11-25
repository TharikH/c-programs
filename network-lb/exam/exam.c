#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>

#define MAX 30

void main(){
    char str[MAX],buf1[MAX],buf2[MAX],c,temp[2]="\0";
    int fd1[2],fd2[2],fd3[2],fd4[2];
    pid_t pid;
    if(pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fd3)< 0 || pipe(fd4) < 0){
        exit(0);
    }
    if(fork() == 0){
        close(fd1[1]);close(fd2[0]);close(fd3[0]);close(fd3[1]);close(fd4[0]);close(fd4[1]);
        int i=0;
        while(read(fd1[0],buf1,2)){
            c=buf1[0];
            if(c == '\0')
                break;
            c+=2;
            if(c > 'z')c-=26;
            str[i++]=c;
        }
        close(fd1[0]);
        printf("child1 - %s \n",str);
        write(fd2[1],str,strlen(str));
        close(fd2[1]);
    }else
    {   
        if(fork() == 0){
        close(fd1[1]);close(fd1[0]);close(fd2[0]);close(fd2[1]);close(fd4[0]);close(fd3[1]);
        int i=0;
        while(read(fd3[0],buf1,2)){
            c=buf1[0];
            if(c == '\0')
                break;
            c+=2;
            if(c > 'z')c-=26;
            str[i++]=c;
        }
        close(fd3[0]);
        printf("child2 - %s \n",str);
        write(fd4[1],str,strlen(str));
        close(fd4[1]);
        }
        else{
            printf("enter string :");
            scanf("%[^\n]s",str);
            printf("string : %s \n",str);
            int len=strlen(str);
            for (int i = 0; i < len; i++)
            {
                temp[0]=str[i];
                if(i%2 == 0){
                    write(fd1[1],temp,2);
                }else{
                    write(fd3[1],temp,2);
                }
            }
            close(fd3[1]);close(fd1[1]);
            read(fd2[0],buf1,len);
            read(fd4[0],buf2,len);
            int k=0,m=0,n=0;
            for (int i = 0; i < len; i++)
            {
                if(i%2 == 0){
                    buf1[m]-=2;
                    if(buf1[m] < 'a')buf1[m]+=26;
                    str[k++]=buf1[m++];
                }else{
                    buf2[n]-=2;
                    if(buf2[n] < 'a')buf2[n]+=26;
                    str[k++]=buf2[n++];
                }
            }
            printf("decrypted string : %s \n",str);
        }
    }
}