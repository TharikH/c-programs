#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 20
#define KEYWORDSLENGTH 5
#define SEPARATORLENGTH 12
char keywords[KEYWORDSLENGTH][10]={"int","if","else","char","void"};
char separator[SEPARATORLENGTH]={',','(',')','}','{','[',']',';','#','<','>'};
char id[30];
int idcount=0,type=0,symbolidenifier=0,point=0;
int isAlpha(char alph){
    if((alph >= 'a' && alph <= 'z') || (alph >= 'a' && alph <= 'z') || alph =='_'){
        return 1;
    }
    return 0;
}
int isnum(char num){
    if(num >= '0' && num <= '9'){
        return 1;
    }
    return 0;
}
int isKeyword(){
    int i=0;
    while (i<KEYWORDSLENGTH)
    {
        if(strcmp(id,keywords[i]) == 0){
            return 1;
        }
        ++i;
    }
    return 0;
}
int isSeparator(char sep){
    int i=0;
    while (i<SEPARATORLENGTH-1){
        if(sep == separator[i]){
            return 1;
        }
        ++i;
    }
    return 0;
}
int isComment(char com,FILE *f){
    if(com == '/'){
        com=fgetc(f);
        if(com == '/'){
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
    }
    return 0;
}
void skipLine(FILE *f){
    char ch;
    while((ch=fgetc(f)) != EOF && ch != '\n');
}
void error(FILE *f,int type){
    fprintf(f,"error type %d --- ",type);
    printf("Error occured \n");
    exit(0);
}
int isOperator(char op,FILE *f){
    id[idcount++]=op;
    switch (op)
    {
    case '+':
        op=fgetc(f);
        if(op == '+' || op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    case '*':
        op=fgetc(f);
        if(op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    case '/':
        op=fgetc(f);
        if(op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    
    case '-':
        op=fgetc(f);
        if(op == '-' || op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    case '=':
        op=fgetc(f);
        if(op == '!' || op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    case '&':
        op=fgetc(f);
        if(op == '&' || op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    case '|':
        op=fgetc(f);
        if(op == '|' || op == '='){
            id[idcount++]=op;
            return 1;
        }
        fseek(f,-1,SEEK_CUR);
        break;
    return 0;
    }
}
int isfullnum(char *num){
    int i=0,dot=1;
    while (num[i] != '\0')
    {
        if(isnum(num[i]) != 1){
        if(num[i] != '.' || dot < 1)
            return 0;
        else
            dot--;
        }
        i++;
    }
    return 1;
}
int isSymtabPresent(char *id){
    FILE *f1=fopen("symtab.txt","r");
    int num;
    char buf[MAX];
    while(fscanf(f1,"%d-%s",&num,buf) != EOF){
        if(strcmp(buf,id)==0){
            fclose(f1);
            return num;
        }
    }
    fclose(f1);
    return -1;

}
void writeToOutput(FILE *f){
    char *str=malloc(sizeof(char) * 30);
    id[idcount]='\0';
    if(isKeyword()){
        fprintf(f,"<keyword,%s>\n",id);
    } 
    else if(type == 1){
        int temp;
        if(isAlpha(id[0])){
            FILE *symtab=fopen("symtab.txt","a");
            if((temp=isSymtabPresent(id)) == -1){
            temp=symbolidenifier++;
            fprintf(symtab,"%d-%s\n",temp,id);
            }
            fclose(symtab);
        if(point == 1){
            fprintf(f,"<pointer,%d>\n",temp);
        }else{
            fprintf(f,"<identifier,%d>\n",temp);
        }
        }else if(isfullnum(id)){
            fprintf(f,"<Number,%s>\n",id);
        }else{
            error(f,1);
        }
    }
    else if(type == 2){
        fprintf(f,"<separator,%s>\n",id);
    }else if(type == 3){
        fprintf(f,"<string,%s>\n",id);
    }else if(type == 4){
        fprintf(f,"<operator,%s>\n",id);
    }
    idcount=0;
    type=0;
    point=0;
}
void main(){
    FILE *input=fopen("input.c","r"),*output=fopen("output.txt","w+");
    char ch;
    while((ch=fgetc(input)) != EOF){
        if(isComment(ch,input)){
            skipLine(input);
        }
        else if(isAlpha(ch) || isnum(ch) || ch == '.' || ch=='_'){
            type=1;
            id[idcount++]=ch;
        }
        else if(isSeparator(ch)){
            writeToOutput(output);
            id[idcount++]=ch;
            type=2;
            writeToOutput(output);
        }
        else if(ch == '"'){
            type=3;
            while((ch=fgetc(input)) != EOF && ch != '"'){
                id[idcount++]=ch;
            }
            if(ch == EOF){
                error(output,0);
            }
            writeToOutput(output);
        }
        else if(ch == '+' || ch == '-' || ch == '/' || ch == '=' || ch == '|' || ch == '&'){
                writeToOutput(output);
                isOperator(ch,input);
                type=4;
                writeToOutput(output);

        }
        else if(ch == '*'){
                writeToOutput(output);
                isOperator(ch,input);
                type=4;
                point=type == 1?0:1;
                writeToOutput(output);
        }
        else if((ch == ' ' || ch =='\t' || ch == '\n') && type != 0){
            writeToOutput(output);
        }
    }
    fclose(input);
    fclose(output);
}
