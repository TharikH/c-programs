#include<stdio.h>
#include<string.h>
#define MAX 10
int vowel_count(char a[]){
    int i=0,count=0;
    while(a[i]!='\0'){
        if(a[i]=='a' || a[i]=='e' || a[i]=='i' || a[i]=='o' || a[i]=='u'){
            count++;
        }
        i++;
    }
    return count;
}
int word_count(char a[]){
    int i=0,count=0;
    while(a[i]!='\0'){
        if(a[i]==' '){
            count++;
        }
        i++;
    }
    return count+1;
}
void prints(char a,char b,int n){
    char c=b;
    for(int i=1;i<= (int)a - (int)b +1;i++){
        printf("%c",c);
        if(i%n==0){
            printf("\n");
        }
        c++;
    }
    printf("\n");
}
void char_print(char a,char b,int n){
    if(a>b){
        prints(a,b,n);
    }
    else{
        prints(b,a,n);
    }
}
void main(){
    char a[MAX];
    printf("enter string\n");
    scanf("%s",a);
    printf("vowel count is:%d \n",vowel_count(a));
    printf("word count is:%d \n",word_count(a));
    char_print('a','z',20);
}