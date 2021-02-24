#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXTEXT 69
int textcount=0;

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
    char *hex = (char *)malloc(sizeof(char) * 7);
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
int hexToDec(char *hex){
    int i=1,len = strlen(hex),val,decimal=0;    
    while(len)  
    {   len--;
        if(hex[len]>='0' && hex[len]<='9')  
        {  
            val = hex[len] - 48;  
        }
        else if(hex[len]>='A' && hex[len]<='F')  
        {  
            val = hex[len] - 65 + 10;  
        }
        decimal += val * i; 
        i*=16;
    }
    return decimal;
}
int binToDec(char *bin){
    int i=1,len=strlen(bin),val,decimal=0;
    while(len){
        len--;
        val=bin[len] - 48;
        decimal+= val*i;
        i*=2;
    }
    return decimal;
}
char *getlength()
{
    char *temp = malloc(sizeof(char) * 5);
    FILE *f = fopen("intermediate.txt", "r");
    fseek(f, -3, SEEK_END);
    fgets(temp, 5, f);
    temp[strlen(temp) - 1] = '\0';
    fclose(f);
    return temp;
}
int findopcode(char *opcode){
    FILE *f=fopen("opcode.txt","r");
    char *op=malloc(sizeof(char) * 20),*val=malloc(sizeof(char) * 20),*format=malloc(sizeof(char) * 20);
    if(f){
        while(!feof(f)){
            fscanf(f,"%s %s %s",op,val,format);
            if(strcmp(op,opcode) == 0){
                return atoi(val);
            }
        }
    }
    return -1;
}
void countText(FILE *f)
{

    char *length = decToHex(textcount/2), temp;
    // printf("check -- %s\n",length);
    if (strlen(length) < 2)
    {
        // printf("check -- %s\n",length);
        temp = length[0];
        length[2] = length[1];
        length[1] = temp;
        length[0] = '0';
    }
    // printf("text--check -- %s\n",length);
    fseek(f, (-(textcount) - 2), SEEK_CUR);
    fprintf(f, "%s", length);
    fseek(f, (textcount), SEEK_CUR);
    textcount = 0;
}
void writeToTextRecord(char *line,char *addr,FILE *f){
    if(strlen(line) + textcount > MAXTEXT){
        countText(f);
        fprintf(f,"T%s  ",addr);
        textcount=0;
    }
    fprintf(f,"%s\n",line);
    textcount+=strlen(line);
}
int validopcode(char *label,char *op,char *value,FILE *f,char *addr){
    char *line=malloc(sizeof(char) * 10);
    if(strcmp(op,"HLT") == 0 || strcmp(op,"RET") == 0){
        int opcode=findopcode(op);
        sprintf(line,"%d0",opcode);
        writeToTextRecord(line,addr,f);
    }
    else if(strcmp(op,"PUSH") == 0 || strcmp(op,"POP") ==0){
        int opcode=findopcode(op);
        char *reg1=malloc(sizeof(char)*4);
        sscanf(value,"%s",reg1);
        sprintf(line,"%d0",opcode);
        writeToTextRecord(line,addr,f);
    }
    else if(strcmp(op,"ADD")== 0 || strcmp(op,"SUB")== 0 || strcmp(op,"MUL")== 0 || strcmp(op,"DIV")== 0){
        char *reg1=malloc(sizeof(char)*4),*reg2=malloc(sizeof(char)*4),*reg3=malloc(sizeof(char)*4);
        sscanf(value,"%s,%s,%s",reg1,reg2,reg3);
        int r1=atoi(++reg1),r2=atoi(++reg2),r3=atoi(++reg3);
        sprintf(line,"%s%s",paddingZero(decToHex(r1),1),paddingZero(decToHex(r2),1));
    }
    return 1;
}
void main(){
    FILE *intm=fopen("intermediate.txt","r"),*object=fopen("object.txt","w");
    char *label=malloc(sizeof(char) * 20),*opcode=malloc(sizeof(char) * 20),*value=malloc(sizeof(char) * 20),*addr=malloc(sizeof(char) * 20);
    int temp;
    if(intm){
        fscanf(intm,"%s\t%s\t%s\t%s",addr,label,opcode,value);
        if(strcmp(opcode,"START") == 0){
            fprintf(object,"H%s%s%s\n",label,addr,getlength());
        }
        while(!feof(intm)){
            fscanf(intm,"%s\t%s\t%s\t%s",addr,label,opcode,value);
            if(validopcode(label,opcode,value,object,addr)){

            }
            else if(strcmp(opcode,"DB") == 0){
                char *line=malloc(sizeof(char) * 10);
                sscanf(line,"%s",paddingZero(decToHex(atoi(value)),3));
                writeToTextRecord(line,addr,object);
            }else if(strcmp(opcode,"EQU") == 0){
                countText(object);
                continue;
            }
            else{
                printf("invalid !");
            }
        }
    }
}