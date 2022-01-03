#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define CHARLENGTH 20
#define MAX 20

/* grammar
E->TE'
E'->+TE' | e
T->FT'
T'->*FT' | e
F->(E) | i
*/
int ind;

void F(char *);
void Tdash(char *);
void T(char *);
void Edash(char *);
void E(char *);

void F(char *input){
    if(input[ind] == '('){
        ind++;
        E(input);
        if(input[ind] == ')'){
            ind++;
        }else{
            printf("rejected\n");
            exit(0);
        }
    }else if(input[ind] == 'i'){
        ind++;
    }else{
        printf("rejected\n");
        exit(0);
    }
}
void Tdash(char *input){
    if(input[ind] == '*'){
        ind++;
        F(input);
        Tdash(input);
    }
}
void T(char *input){
    F(input);
    Tdash(input);
}
void Edash(char *input){
    if(input[ind] == '+'){
        ind++;
        T(input);
        Edash(input);
    }
}
void E(char *input){
    T(input);
    Edash(input);
}


void main(){
    char *input = malloc(sizeof(char) * CHARLENGTH);
    ind=0;
    printf("enter input");
    scanf("%s",input);
    E(input);
    printf("Accepted the string\n");
}