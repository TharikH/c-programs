#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTLENGTH 60
int textcount = 0,pc=1,base=1;
char executionstart[6];
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
void indexAddress(char *hex)
{
    int temp = hex[0] - 48;
    temp += 8;
    if (temp < 10)
    {
        hex[0] = temp + 48;
    }
    else
    {
        hex[0] = temp + 55;
    }
}
char *isIndexing(char *operand)
{
    char **split = (char **)malloc(sizeof(char *) * 2);
    split[0] = (char *)malloc(sizeof(char) * 6);
    split[1] = (char *)malloc(sizeof(char) * 6);
    split_by_delimeter(operand, split, ',');
    if (strcasecmp(split[1], "X") == 0)
    {
        return split[0];
    }
    else
    {
        return NULL;
    }
}

char *getlength()
{
    char *temp = malloc(sizeof(char) * 5);
    FILE *f = fopen("intermediate.txt", "r");
    fseek(f, -4, SEEK_END);
    fgets(temp, 5, f);
    temp[strlen(temp) - 1] = '\0';
    fclose(f);
    return temp;
}
char *getName(char *line)
{
    char *name = malloc(sizeof(char) * 7);
    int j = 0, i = 0;
    for (i = 0; i < 6; i++)
    {
        if (line[j] != '\0')
        {
            name[i] = line[j];
            j++;
        }
        else
        {
            name[i] = ' ';
        }
    }
    name[i] = '\0';
    return name;
}
void writeToList(char *list)
{
    FILE *f = fopen("list.txt", "a");
    fprintf(f, "%s\n", list);
    fclose(f);
}
char *findOpcodeAddress(char *opcode, char *format)
{
    FILE *f = fopen("opcode.txt", "r");
    char *line = (char *)malloc(sizeof(char) * 30);
    while (fgets(line, 30, f) != NULL)
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[--len] = '\0';
        }
        char **split = (char **)calloc(3, sizeof(char *));
        // char split[2][6];
        split[0] = (char *)malloc(sizeof(char) * 6);
        split[1] = (char *)malloc(sizeof(char) * 6);
        split[2] = (char *)malloc(sizeof(char) * 6);
        split_by_delimeter(line, split, ' ');
        // printf("line:%s\n", line);
        // printf("look --%s-%s-%s\n", split[0], split[1],split[2]);
        if (strcasecmp(split[0], opcode) == 0)
        {
            fclose(f);
            strcpy(format,split[2]);
            // printf("opc --  --  %s",split[2]);
            format = split[2];
            // printf("nokk -- %s\n",format);
            return split[1];
        }
        free(split);
    }
    free(line);
    fclose(f);
    return NULL;
}
char *findLabelAddress(char *label)
{
    FILE *f = fopen("symbol.txt", "r");
    char *line = (char *)malloc(sizeof(char) * 30);
    while (fgets(line, 30, f) != NULL)
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[--len] = '\0';
        }
        char **split = (char **)malloc(sizeof(char *) * 2);
        split[0] = (char *)malloc(sizeof(char) * 6);
        split[1] = (char *)malloc(sizeof(char) * 6);
        split_by_delimeter(line, split, '\t');
        if (strcasecmp(split[0], label) == 0)
        {
            fclose(f);
            return split[1];
        }
    }
    fclose(f);
    return NULL;
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
void formatTwo(char *opcode, char *label, char *text)
{
    char **split = malloc(sizeof(char *) * 2);
    FILE *f = fopen("register.txt", "r");
    char line[20];
    int i = 2;
    text[0] = opcode[0];
    text[1] = opcode[1];
    split[0] = malloc(sizeof(char) * 2);
    split[1] = malloc(sizeof(char) * 2);
    split[0][0] = '\0';
    split[1][0] = '\0';
    split_by_delimeter(label, split, ',');
    if (split[1][0] == '\0')
    {
        text[2] = '0';
        i = 3;
    }
    while (fgets(line, 20, f))
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[--len] = '\0';
        }
        char **splitted = malloc(sizeof(char *) * 2);
        splitted[0] = malloc(sizeof(char) * 2);
        splitted[1] = malloc(sizeof(char) * 2);
        split_by_delimeter(line, splitted, ' ');
        if (splitted[0][0] == split[0][0])
        {
            text[i] = splitted[1][0];
        }
        if (splitted[0][0] == split[1][0])
        {
            text[i + 1] = splitted[1][0];
        }
    }
    text[4]='\0';
}
void writeToModification(char *address){
    FILE *f=fopen("modification.txt","a");
    char *addr=malloc(sizeof(char) * 7);
    addr=paddingZero(address,6);
    fprintf(f,"M%s05\n",addr);
    fclose(f);
}
void copyModification(FILE *f){
    char *line=malloc(sizeof(char) * 12);
    FILE *fmod=fopen("modification.txt","r");
    fprintf(f,"\n");
    while(fgets(line,12,fmod) != NULL){
        fprintf(f,"%s",line);
    }
    fclose(fmod);
}
void formatFour(char *opcode,char *label,char *text,char *nixbpe,char *address){
    int temp;
    char ni[]="11\0",*xbpe=malloc(sizeof(char) * 5),*addr=malloc(sizeof(char) * 7),*templabel=malloc(sizeof(char) * 7);
    nixbpe[5]='1';
    if(isIndexing(label) != NULL){
        nixbpe[2]='1';
    }
    nixbpe+=2;
    if((templabel=isIndexing(label)) != NULL){
        nixbpe[0]='1';
        addr=findLabelAddress(templabel);
    }
    else{
        addr=findLabelAddress(label);
    }
    addr=paddingZero(addr,5);
    temp=hexToDec(opcode)+binToDec(ni);
    opcode=paddingZero(decToHex(temp),2);
    xbpe=decToHex(binToDec(nixbpe));
    // printf("checkcorr -- %s - %s -%s\n",opcode,xbpe,addr);
    sprintf(text,"%s%s%s",opcode,xbpe,addr);
    writeToModification(address);
}
char * negativeHex(int symbol,int curr){
    int ffff=65535,temp;
    char * addr=malloc(sizeof(char) * 7);
    temp=symbol+ffff-curr+1;
    addr=decToHex(temp);
    addr++;
    return addr;
}
void formatThree(char *opcode,char *label,char *text,char *nixbpe,char *address){
    char ni[]="11\0",*xbpe=malloc(sizeof(char) * 5),*addr=malloc(sizeof(char) * 7),*templabel=malloc(sizeof(char) * 7);
    int current_address,symbol_adress,displacement,temp;
    if(pc){
        nixbpe[4]='1';
    }
    else{
        nixbpe[3]='1';
    }
    nixbpe+=2;
    temp=hexToDec(opcode)+binToDec(ni);
    opcode=paddingZero(decToHex(temp),2);
    xbpe=decToHex(binToDec(nixbpe));
    current_address=hexToDec(address);
    if((templabel=isIndexing(label)) != NULL){
        nixbpe[0]='1';
        // printf("check -- %s\n",addr);
        addr=findLabelAddress(templabel);
        
    }
    else{
        if(label[0] == '\0'){
            sprintf(text,"%s0000",opcode);
            return;

        }
        addr=findLabelAddress(label);

        printf("check -- %s --%s\n",addr,label);
    }
    symbol_adress=hexToDec(addr);
    if((displacement=symbol_adress-current_address)>0)
    {
        addr=paddingZero(decToHex(displacement),3);
    }
    else{
        addr=negativeHex(symbol_adress,current_address);
    }
    sprintf(text,"%s%s%s",opcode,xbpe,addr);
}
void getAddressandOtherInfo(int format, char *opcode, char *label, char *nixbpe, char *text,char *address)
{

    switch (format)
    {
    case 1:
        text = opcode;
        break;
    case 2:
        formatTwo(opcode, label, text);
        break;
    case 3:
        formatThree(opcode,label,text,nixbpe,address);
        break;
    case 4:
        formatFour(opcode,label,text,nixbpe,address);
        break;
    default:
        break;
    }
}
void writeToTextRecord(char *opcode, char *address, char *label, FILE *f)
{
    char *op = malloc(sizeof(char) * 6), *format = malloc(sizeof(char) * 2), *labeladdress = malloc(sizeof(char) * 7),
         nixbpe[] = "000000\0", *text = malloc(sizeof(char) * 10);
    int count=0;
    switch (label[0])
    {
    case '@':
        nixbpe[0] = 1;
        label++;
        break;
    case '#':
        nixbpe[1] = 1;
        label++;
        break;
    default:
        nixbpe[0] = 1;
        nixbpe[1] = 1;
        break;
    }
    op = findOpcodeAddress(opcode, format);
    // printf("format -%s\n",format);
    sscanf(format, "%d", &count);
    // printf("format - %d\n",count);
    getAddressandOtherInfo(count, op, label, nixbpe, text,address);
    // printf("\ntext -- %s -- address -- %s\n",text,address);
    count*=2;
    if (textcount == 0 || textcount + count > TEXTLENGTH)
    {
        if (textcount + count > TEXTLENGTH)
        {
            countText(f);
        }
        fprintf(f, "\nT%s  %s", address, text);
    }
    else
    {
        fprintf(f, "%s", text);
    }
    free(op);
    free(labeladdress);
    printf("%s\n",text);
    textcount = textcount + count;
    // printf("\ntextcount  ---- %d\n",count);
}
int secondPass(char **line, FILE *f)
{
    char opcode[5], address[6], label[8];
    // fprintf(f,"hello kutta");
    // printf("%s-%s-%s-%s\n", line[0], line[1], line[2],line[3]);
    if (strcmp(line[2], "START") == 0)
    {
        strcpy(executionstart, line[0]);
        fprintf(f, "H%s00%s00%s", getName(line[1]), line[0], getlength());
    }
    else if (strcasecmp(line[1], "END") == 0)
    {
        int loc;
        if (line[2][0] != '\0')
        {
            strcpy(executionstart, line[2]);
        }
        sscanf(executionstart, "%d", &loc);
        if (textcount != 0)
        {
            // printf("at end!\n");
            countText(f);
        }
        copyModification(f);
        fprintf(f, "E00%s", paddingZero(decToHex(loc),4));
        return 0;
    }
    else if(strcasecmp(line[1],"BASE") == 0){
        pc=0;
        base=1;
    }
    else if(strcasecmp(line[1],"NOBASE") == 0){
        pc=1;
        base=0;
    }
    else if (strcasecmp(line[2], "RESW") == 0 || strcasecmp(line[2], "RESB") == 0)
    {
        if (textcount != 0){
            countText(f);
        }
            
    }
    else if (strcasecmp(line[2], "WORD") == 0)
    {
        strcpy(label, line[3]);
        strcpy(address, line[0]);
        int temp;
        sscanf(label, "%d", &temp);
        // writeToTextRecord(opcode,paddingZero(decToHex(temp)),address,f);
        if (textcount == 0 || textcount + 6 > TEXTLENGTH)
        {
            if (textcount + 6 > TEXTLENGTH)
            {
                countText(f);
            }
            fprintf(f, "\nT%s  00%s", address, paddingZero(decToHex(temp),4));
            printf("%s\n",paddingZero(decToHex(temp),6));
        }
        else
        {
            fprintf(f, "00%s", paddingZero(decToHex(temp),4));
            printf("%s\n",paddingZero(decToHex(temp),6));
        }
        textcount += 6;
    }
    else if (strcasecmp(line[2], "BYTE") == 0)
    {
        char **split = (char **)malloc(sizeof(char *) * 3);
        split[0] = (char *)malloc(sizeof(char) * 3);
        split[1] = (char *)malloc(sizeof(char) * 3);
        split[2] = (char *)malloc(sizeof(char) * 3);
        split[0][0] = '\0';
        split[1][0] = '\0';
        split[2][0] = '\0';
        strcpy(address, line[0]);
        split_by_delimeter(line[3], split, '\'');
        // printf("test -- %s %s %s\n",split[0],split[1],split[2]);
        if (split[0][0] == 'X')
        {
            strcpy(label, split[1]);
        }
        // printf(" check - %s\n", address);
        if (textcount == 0 || textcount + 2 > TEXTLENGTH)
        {
            if (textcount + 2 > TEXTLENGTH)
            {
                countText(f);
            }
            fprintf(f, "\nT%s  %s", address, label);
        }
        else
        {
            fprintf(f, "%s", label);
        }
        printf("%s\n",label);
        textcount += 2;
    }
    else if (line[3][0] == '\0')
    {
        strcpy(opcode, line[1]);
        strcpy(address, line[0]);
        strcpy(label, line[2]);
        // printf("Error:%s-%s-%s\n", opcode, address, label);
        writeToTextRecord(opcode, address, label, f);
    }
    else if (line[3][0] != '\0')
    {
        strcpy(opcode, line[2]);
        strcpy(address, line[0]);
        strcpy(label, line[3]);
        // printf("%s-%s-%s\n",opcode,address,label);
        writeToTextRecord(opcode, address, label, f);
    }
    else
    {
        printf("Error in program! please do the needful");
    }
    return 1;
}
void main()
{
    FILE *f;
    char *line = (char *)malloc(sizeof(char) * 50);
    f = fopen("intermediate.txt", "r");
    // char ch[]="2AB";
    // char ch1[]="0010";
    // printf("%d\n",hexToDec(ch));
    // printf("%d\n",binToDec(ch1));
    // char *trial=malloc(sizeof(char) * 7);
    // trial=negativeHex(6,26);
    // printf("%s\n",trial);
    // return;
    FILE *fo = fopen("object.txt", "w+");
    if (f)
    {
        while (fgets(line, 50, f) != NULL)
        {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n')
            {
                line[--len] = '\0';
            }
            char **split_code = (char **)malloc(sizeof(char *) * 4);
            split_code[0] = (char *)malloc(sizeof(char) * 8);
            split_code[1] = (char *)malloc(sizeof(char) * 8);
            split_code[2] = (char *)malloc(sizeof(char) * 8);
            split_code[3] = (char *)malloc(sizeof(char) * 8);
            split_code[3][0] = '\0';
            split_code[2][0] = '\0';
            split_by_delimeter(line, split_code, '\t');
            if (split_code[0][0] == '.')
            {
                writeToList(line);
            }
            else
            {
                writeToList(line);
                if (!secondPass(split_code, fo))
                {
                    break;
                }
            }
            // printf("%s-%s-%s-%s\n", split_code[0], split_code[1], split_code[2], split_code[3]);
            free(split_code);
            // printf("%s ",line);
        }
        fclose(f);
        fclose(fo);
    }
    else
    {
        printf("Error no intermediate found! please finish first pass!");
    }
}