#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
    char *hello=malloc(sizeof(char) *5);
    strcpy(hello,"hello");
    printf("%s\n",hello);
    hello+=2;
    printf("%s\n",hello);
}