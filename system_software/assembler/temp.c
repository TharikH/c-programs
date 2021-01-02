#include<stdio.h>
#include<stdlib.h>
void funct(FILE *f){
    fprintf(f,"Hello kuttta how are you!");
    fseek(f,-4,SEEK_CUR);
    fprintf(f,"Mutta");
}
void main(){
    FILE *f=fopen("temp.txt","a");
    funct(f);
    fclose(f);
}