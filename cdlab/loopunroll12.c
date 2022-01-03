#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int isAlphaNum(char ch){
    if(ch >= 'a' && ch <= 'z' || ch >='A' && ch <= 'Z' || ch >= '0' && ch < '9'){
        return 1;
    }
    return 0;
}
int isAlpha(char *arr,int *i){
    int flag = 0;
    while (isAlphaNum(arr[*i]))
    {
        flag = 1;
        (*i)++;
    }
    (*i)--;
    return flag;
}
int findCount(char *arr){
    int i=0,start=0,end=0,inc=0,step=0,count=0;;
    while(arr[i] != ';'){
        if(isAlpha(arr,&i)){
            start = arr[i+2] - '0';
            break;
        }
        i++;
    }
    while(arr[i] != ';')i++;
    i++;
    while(arr[i] != ';'){
        if(isAlpha(arr,&i)){
            end = arr[i+2] - '0';
            if(arr[i+1] == '<'){
                inc = 1;
            }
            break;
        }
        i++;
    }
    while(arr[i] != ';')i++;
    i++;
    while(arr[i] != '\0'){
        if(isAlpha(arr,&i)){
            if(arr[i+1] == '+' || arr[i+1] == '-'){
                step=1;
            }else if(arr[i+1] == '='){
                if(arr[i+4] != '\0'){
                    step=arr[i+4] - '0';
                }
            }
            break;
        }
        i++;
    }
    if(inc){
        while(start < end){
            count++;
            start += step;
        }
    }else{
        while(start > end){
            count++;
            start -=step;
        }
    }
    return count;
}
void main(){
    FILE *in=fopen("input.c","r"),*out=fopen("output.c","w");
    char ch,forstore[MAX],contentstore[MAX];
    int k=0,count=0;

    while((ch=fgetc(in)) != EOF){
        if(ch == 'f'){
            ch=fgetc(in);
            if(ch == 'o'){
                ch=fgetc(in);
                if(ch == 'r'){
                ch=fgetc(in);
                if(ch == '('){
                    k=0;
                    while ((ch=fgetc(in)) != ')')
                    {
                        forstore[k++]=ch;
                    }
                    forstore[k]='\0';
                    // printf(" >> %s ",forstore);
                    count=findCount(forstore);
                    // printf(" -- %d",count);
                    k=0;
                    while(ch = fgetc(in) != '{');
                    ch = fgetc(in);
                    while((ch = fgetc(in)) != '}'){
                        contentstore[k++]=ch;
                    }
                    contentstore[k]='\0';
                    // printf("== %s",contentstore);
                    while(count-- ){
                        k=0;
                        while(contentstore[k] != '\0'){
                            fputc(contentstore[k],out);
                            k++;
                        }
                    }
                }
                else{
                    fseek(in,-3,SEEK_CUR);
                    goto L1;
                }
            }else{
                fseek(in,-2,SEEK_CUR);
                goto L1;
            }
            }
            else{
                fseek(in,-1,SEEK_CUR);
                goto L1;
            }
        }else{
            L1:
            fputc(ch,out);
        }
    }
}