#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int locctr=0,equ=0;
char *paddingZero(char *hex,int count)
{
    char *addr = (char *)malloc(sizeof(char) * (count+1));
    int valid = strlen(hex) - 1, i = count-1;
    for (int j = 0; j < count; j++)
    {
        if (valid >= 0)
        {
            addr[i] = hex[valid];
        }
        else
        {
            addr[i] = '0';
        }
        i--;
        valid--;
    }
    addr[count] = '\0';
    return addr;
}
char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}
char *decToHex(int num)
{
    int temp, i = 0;
    char *hex = (char *)malloc(sizeof(char) * 5);
    while (num != 0)
    {
        temp = num % 16;
        if (temp < 10)
        {
            hex[i] = temp + 48;
        }
        else
        {
            hex[i] = temp + 55;
        }
        i++;
        num /= 16;
    }
    hex[i] = '\0';
    hex = strrev(hex);
    return hex;
}
int opcodeval(char *opcode){
    FILE *f=fopen("opcode.txt","r");
    char *op=malloc(sizeof(char) * 20),*val=malloc(sizeof(char) * 20),*format=malloc(sizeof(char) * 20);
    if(f){
        while(!feof(f)){
            fscanf(f,"%s %s %s",op,val,format);
            if(strcmp(op,opcode) == 0){
                return atoi(format);
            }
        }
    }
    return -1;
}
int duplicateSymbol(char *symb){
    FILE *f=fopen("symbol.txt","r");
    char *sym=malloc(sizeof(char) * 20),*addr=malloc(sizeof(char) * 20);
    int abs;
    if(f){
        while(!feof(f)){
            fscanf(f,"%s %s %d",sym,addr,&abs);
            if(strcmp(sym,symb) == 0){
                return 1;
            }
        }
        fclose(f);
    }
    return 0;
}
void writeToSymbol(char *label,int abs){
    if(label[0] == '-'){
        return;
    }
    FILE *f=fopen("symbol.txt","a");
    if(f){
        if(!duplicateSymbol(label)){
            if(abs){
                fprintf(f,"%s %s %d\n",label,paddingZero(decToHex(equ),3),abs);
            }
            else{
            fprintf(f,"%s %s %d\n",label,paddingZero(decToHex(locctr),3),abs);
            }
        }
        else{
            printf("duplication");
            exit(0);
        }
        fclose(f);
    }
    
}
void writeToIntermediate(char *addr,char *label,char *opcode,char *value,FILE *intmt){
    // if(label[0])
    fprintf(intmt,"%s\t%s\t%s\t%s\n",addr,label,opcode,value);
}
void main(){
    FILE *source=fopen("source.txt","r"),*intmt=fopen("intermediate.txt","w");
    char *label=malloc(sizeof(char) * 20),*opcode=malloc(sizeof(char) * 20),*value=malloc(sizeof(char) * 20);
    int temp;
    if(source){
        fscanf(source,"%s %s %s",label,opcode,value);
        if(strcmp(opcode,"START") == 0){
            if(value[0] != '\0'){
                locctr=atoi(value);
            }
            writeToIntermediate(paddingZero(decToHex(locctr),3),label,opcode,value,intmt);
        }
        while(!feof(source)){
            // char *label=malloc(sizeof(char) * 20),*opcode=malloc(sizeof(char) * 20),*value=malloc(sizeof(char) * 20);
            fscanf(source,"%s %s %s",label,opcode,value);
            if(strcmp(opcode,"END") == 0){
                writeToIntermediate(paddingZero(decToHex(locctr),3),label,opcode,value,intmt);
                fprintf(intmt,"count:%s",paddingZero(decToHex(locctr),3));
                break;
            }
            else if((temp=opcodeval(opcode)) != -1){
                writeToIntermediate(paddingZero(decToHex(locctr),3),label,opcode,value,intmt);
                printf("%s h %s h %s\n",label,opcode,value);
                writeToSymbol(label,0);
                locctr+=temp;
            }
            else if(strcmp(opcode,"DB") == 0){
                writeToIntermediate(paddingZero(decToHex(locctr),3),label,opcode,value,intmt);
                writeToSymbol(label,0);
                printf("hello - %d\n",locctr);
                locctr+=1;
            }
            else if(strcmp(opcode,"EQU") == 0){

                writeToIntermediate(paddingZero(decToHex(locctr),3),label,opcode,value,intmt);
                equ=atoi(value);
                writeToSymbol(label,1);
            }
            else{
                printf("error! invalid symbol ,%s %s %s \n",label,opcode,value);
            }
        }
    }
}