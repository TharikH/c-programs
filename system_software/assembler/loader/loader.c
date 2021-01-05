#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//macros
#define removeNewLineCharacter(line)\
    size_t len = strlen(line);\
    if (len > 0 && line[len - 1] == '\n')\
    {\
    line[--len] = '\0';\
    }

#define readCharacter(input, output, count) \
    for (int i = 0; i < count; i++)         \
    {                                       \
        output[i] = input[i];               \
    }                                       \
    output[count] = '\0';                   \
    input += count;

#define allocate(type, size) malloc(sizeof(type) * size)

//functions

//function to reverse string
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

//function to add additional zeroes infront of it so as to make correct padding
char *paddingZero(char *hex, int count)
{
    char *addr = (char *)malloc(sizeof(char) * (count + 1));
    int valid = strlen(hex) - 1, i = count - 1;
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

//function to convert decimal to hexadecimal
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

//function to convert decimal to hexadecimal
int hexToDec(char *hex)
{
    int i = 1, len = strlen(hex), val, decimal = 0;
    while (len)
    {
        len--;
        if (hex[len] >= '0' && hex[len] <= '9')
        {
            val = hex[len] - 48;
        }
        else if (hex[len] >= 'A' && hex[len] <= 'F')
        {
            val = hex[len] - 65 + 10;
        }
        decimal += val * i;
        i *= 16;
    }
    return decimal;
}

//function to control errors
void errorSection(int error){
    switch (error)
    {
    case 1:
        printf("No Header found!\n");
        exit(1);
    case 2:
        printf("Not able to find header/end record!\n");
        exit(1);
    case 3:
        printf("Object file not created!\n");
        exit(1);
    case 4:
        printf("Textlength exceeded than specified!\n");
        exit(1);
    default:
        printf("Unknown error!\n");
        exit(1);
    }
}

//function to read do the necessary thing for textrecords
void readTextRecords(FILE *objectfile, FILE *loaderfile, int addresscounter, int total_length)
{
    int columncount=0,reserve_count=0,length=0;
    char *line=allocate(char,70),*temp=allocate(char,10);
    while(fgets(line,70,objectfile) != NULL){
        removeNewLineCharacter(line);
        if(line[0] == 'E'){
            return;
        }
        else if(line[0] == 'T'){
            line++;
            readCharacter(line,temp,4);
            reserve_count=hexToDec(temp);
            readCharacter(line,temp,2);
            length=hexToDec(temp);
            printf("line -%d -%d\n",reserve_count,addresscounter);
            while(reserve_count > addresscounter){
                printf("\nhello\n");
                if(columncount > 5){
                    fprintf(loaderfile,"\n");
                    columncount=0;
                }
                fprintf(loaderfile,"%s   XX\t",paddingZero(decToHex(addresscounter),4));
                addresscounter++;
                columncount++;
                addresscounter<=total_length?NULL:errorSection(4);
            }
            while(length--){
                if(columncount > 5){
                    fprintf(loaderfile,"\n");
                    columncount=0;
                }
                fprintf(loaderfile,"%s   %c%c\t",paddingZero(decToHex(addresscounter),4),line[0],line[1]);
                line+=2;
                columncount++;
                addresscounter++;
                addresscounter<=total_length?NULL:errorSection(4);
            }
        }
        else{
            errorSection(2);
        }
    }
}
//Main function
void main()
{
    char *headrecord = allocate(char, 20),*sixcharacter = allocate(char, 7);
    int addresscounter = 0, total_length = 0;
    FILE *objectfile = fopen("object.txt", "r"),
         *loaderfile = fopen("loader.txt", "w");

    if(!objectfile){
        errorSection(3);
    }
    fgets(headrecord, 20, objectfile);
    if (headrecord[0] == 'H')
    {
        headrecord++;
        printf("%s",headrecord);
        readCharacter(headrecord, sixcharacter, 6);
        printf("program name : %s\n", sixcharacter);
        readCharacter(headrecord, sixcharacter, 6);
        addresscounter = hexToDec(sixcharacter);
        readCharacter(headrecord, sixcharacter, 6);
        total_length = hexToDec(sixcharacter);
        readTextRecords(objectfile, loaderfile, addresscounter, total_length);

        fclose(objectfile);
        fclose(loaderfile);
    }
    else
    {
        errorSection(1);
    }
    free(sixcharacter);
}