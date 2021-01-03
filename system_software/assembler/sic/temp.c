#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void funct(FILE *f){
    fprintf(f,"Hello kuttta how are you!");
    fseek(f,-4,SEEK_CUR);
    fprintf(f,"Mutta");
}
void main(){
    char *length=malloc(sizeof(char) * 4);
    char temp;
    strcpy(length,"C9");
    if(strlen(length) < 2){
        printf("check -- %c %c %c\n",length[0],length[1],length[2]);
        temp=length[0];
        length[1]=temp;
        length[0]='0';
        length[3]='\0';
        printf("check -- %c %c %c\n",length[0],length[1],length[2]);
    }
}