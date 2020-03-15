#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX 10
int len(char a[]){                                      //returns string length
    int i=0;
    while(a[i]!='\0'){
        i++;
    }
    return i;
}
char* reverse(char a[]){   
    int k=len(a);                                //reverses the string
    char rev[k];
    int j=0;
    for(int i=k-1;i>=0;i--,j++){
        rev[j]=a[i];
    }
    rev[j]='\0';
    char *revers=rev;
    return revers;
}
void pallindrome(char a[]){
    for(int i=0;i<len(a);i++){
        tolower(a[i]);                                          //so lower and upper taken equally
    }
    char* rev=reverse(a);
    if(strcmp(a,rev)==0){
        printf("yes");
    }
    else{
        printf("no");
    }
}
void main(){
    char a[MAX];
    printf("enter string\n");
    scanf("%s",a);
    pallindrome(a);
}