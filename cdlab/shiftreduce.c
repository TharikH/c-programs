#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHARLENGTH 20
#define MAX 20
char stack[MAX];
int top = -1;

void push(char value){
    if(top == MAX - 1){
        printf("underflow");
    }else{
        stack[++top] = value;
    }
}
char pop(){
    char temp ='\0';
    if(top == -1){
        printf("underflow");
    }else{
        temp=stack[top];
        stack[top] = '\0';
        top--;
    }
    return temp;
}
int isReducible(char ** production,int num){
    char *prod;
    int j=0,flag,len;
    for (int i = 0; i < num; i++)
    {
        prod=production[i]+3;
        j=0;
        flag = 0;
        len = strlen(prod);
        while(prod[j] != '\0'){
            // printf(" == %d %d\n",top,len);
            if(stack[top -  len +j+1] == prod[j]){
                j++;
            }else{
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            // printf("%s -- %s\n",production[i],stack);
            return i;
        }
    }
    return -1;
}
void reduce(char **production,int num,char *input){
    int len,index;
    char temp;
    index=isReducible(production,num);
    if(index > -1){
        len=strlen(production[index] + 3);
        while(len--){
            temp = pop();
        }
        push(production[index][0]);
        printf("reduce %s\n",production[index]);
        printf("%s\t%s\t",stack,input);
        reduce(production,num,input);
        
    }
}
void shiftreduce(char **production,char *input,int num){
    push('$');
    int i=0;
    printf("stack\tinput\tnext\n");
    printf("%s\t%s\t",stack,input);
    while(input[i] != '\0'){
        // printf("%s\t%s\t",stack,input+i);
        push(input[i]);
        i++;
        printf("shift\n");
        printf("%s\t%s\t",stack,input+i);
        // printf("%s\t%s\t",stack,input+i);
        reduce(production,num,input+i);
    }
    if(stack[0] == '$' && stack[1] == production[0][0] && stack[2] == '$'){
        printf("Accepted\n");
    }
    else{
        printf("Rejected\n");
    }
}
void main(){
    int num=4,len;
    printf("enter number of production :");
    scanf("%d",&num);
    printf("enter production:\n");
    char **production=malloc(sizeof(char *) * num),*input=malloc(sizeof(char) * CHARLENGTH);
    for (int i = 0; i < num; i++)
    {
        production[i]=malloc(sizeof(char) * CHARLENGTH);
        scanf("%s",production[i]);
    }
    printf("enter input:");
    scanf("%s",input);
    len=strlen(input);
    input[len]='$';input[len+1]='\0';

    // strcpy(production[0],"E->E*E");strcpy(production[1],"E->E+E");
    // strcpy(production[2],"E->(E)");strcpy(production[3],"E->i");
    shiftreduce(production,input,num);
}