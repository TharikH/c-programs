#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXSYMBLEN 100
int symblen=0,locctr=0;
struct address_struct{
    char address[6];
    struct address_struct *next;
};
struct symbolstruct{
    char symbol[6];
    char value[6];
    struct address_struct *addr;
}SYMTAB[MAXSYMBLEN];

void split_by_delimeter(char *line, char **splitted, char delimeter)
{
    char ch;
    int i = 0, k = 0, j = 0;
    while ((ch = line[i]) != '\0')
    {
        if (ch != delimeter)
        {
            splitted[k][j++] = ch;
        }
        else
        {
            if (line[i + 1] != delimeter)
            {
                splitted[k][j] = '\0';
                k++;
                j = 0;
            }
        }
        i++;
    }
    splitted[k][j] = '\0';
}
char *paddingDelimeter(char *hex,int count,char delimeter)
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
            addr[i] = delimeter;
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
    char *hex = (char *)malloc(sizeof(char) * 4);
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
void onePass(char **split,FILE *obj){
    if(strcasecmp(split[1],"START") == 0){
        
    }
}
void main(){
    FILE *source=fopen("source.txt","r"),*obj=fopen("object.txt","w");
    char *line = (char *)malloc(sizeof(char) * 50);
    if (source)
    {
        while (fgets(line, 50, source) != NULL)
        {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n')
            {
                line[--len] = '\0';
            }
            char **split_code = (char **)malloc(sizeof(char *) * 3);
            split_code[0] = (char *)malloc(sizeof(char) * 8);
            split_code[1] = (char *)malloc(sizeof(char) * 8);
            split_code[2] = (char *)malloc(sizeof(char) * 8);
            split_code[0][0] = '\0';
            split_code[1][0] = '\0';
            split_code[2][0] = '\0';
            split_by_delimeter(line, split_code, ' ');
            if (split_code[0][0] == '.')
            {
                continue;
            }
            else
            {
                if (!onePass(split_code, obj))
                {
                    break;
                }
            }
            printf("%s-%s-%s\n", split_code[0], split_code[1], split_code[2]);
            free(split_code);
            // printf("%s ",line);
        }
        fclose(obj);
        fclose(source);
    }
    else
    {
        printf("Error no intermediate found! please finish first pass!");
    }
}