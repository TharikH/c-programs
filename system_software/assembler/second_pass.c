#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTLENGTH 30
int textcount = 0;
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
char *paddingZero(char *hex)
{
    char *addr = (char *)malloc(sizeof(char) * 5);
    int valid = strlen(hex) - 1, i = 3;
    for (int j = 0; j < 4; j++)
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
    addr[4] = '\0';
    return addr;
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
char* isIndexing(char *operand)
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
char *findOpcodeAddress(char *opcode)
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
        char **split = (char **)calloc(2, sizeof(char *));
        // char split[2][6];
        split[0] = (char *)malloc(sizeof(char) * 6);
        split[1] = (char *)malloc(sizeof(char) * 6);
        split_by_delimeter(line, split, ' ');
        // printf("line:%s\n", line);
        // printf("%s-%s\n", split[0], split[1]);
        if (strcasecmp(split[0], opcode) == 0)
        {
            fclose(f);
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

    char *length=decToHex(textcount);
    printf("%s\n",length);
    if(strlen(length) < 2){
        length[1]=length[0];
        length[0]='0';
        length[3]='\0';
    }
    fseek(f, (-(textcount*2)-2), SEEK_CUR);
    printf("%ld\n",ftell(f));
    // printf("%s\n%d",decToHex(textcount),-textcount-2);
    fprintf(f, "%s", length);
    fseek(f, (textcount*2), SEEK_CUR);
    printf("%ld\n",ftell(f));
    textcount = 0;
}
void writeToTextRecord(char *opcode, char *address, char *label, FILE *f)
{
    char *op = malloc(sizeof(char) * 6), *labeladdress = malloc(sizeof(char) * 7);
    op = findOpcodeAddress(opcode);
    if(label[0] == '\0'){
        strcpy(labeladdress,"0000");
    }
    else if((labeladdress=isIndexing(label)) != NULL){
        labeladdress = findLabelAddress(labeladdress);
        indexAddress(labeladdress);
    }
    else{
        labeladdress = findLabelAddress(label);
    }
    if (textcount == 0 || textcount + 3 > TEXTLENGTH)
    {
        if(textcount + 3 > TEXTLENGTH){
            countText(f);
        }
        fprintf(f, "\nT%s  %s%s", address, op, labeladdress);
    }
    else
    {
        fprintf(f, "%s%s", op, labeladdress);
    }
    free(op);
    free(labeladdress);
    textcount = textcount + 3;
}
int secondPass(char **line,FILE *f)
{
    char opcode[5], address[6], label[8];
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
        if(textcount != 0){
            countText(f);
        }
        fprintf(f, "\nE00%s", paddingZero(decToHex(loc)));
        return 0;
    }
    else if(strcasecmp(line[2],"RESW") == 0 || strcasecmp(line[2],"RESB") == 0){
        if(textcount != 0)
            countText(f);
    }
    else if(strcasecmp(line[2],"WORD") == 0){
        strcpy(label, line[3]);
        strcpy(address, line[0]);
        int temp;
        sscanf(label,"%d",&temp);
        // writeToTextRecord(opcode,paddingZero(decToHex(temp)),address,f);
        if(textcount == 0 || textcount+3>TEXTLENGTH){
            if(textcount+3>TEXTLENGTH){
                countText(f);
            }
            fprintf(f, "\nT%s  00%s", address,paddingZero(decToHex(temp)));
        }else{
            fprintf(f,"00%s",paddingZero(decToHex(temp)));
        }
        textcount+=3;
    }
    else if(strcasecmp(line[2],"BYTE") == 0){
        char **split=(char **)malloc(sizeof(char *) * 3);
        split[0]=(char *)malloc(sizeof(char) * 3);
        split[1]=(char *)malloc(sizeof(char) * 3);
        split[2]=(char *)malloc(sizeof(char) * 3);
        split_by_delimeter(line[3],split,'\'');
        if(split[0][0] == 'X'){
            strcpy(label,split[1]);
        }
        if(textcount == 0 || textcount+1>TEXTLENGTH){
            if(textcount+1>TEXTLENGTH){
                countText(f);
            }
            fprintf(f, "\nT%s  %s", address,label);
        }else{
            fprintf(f,"%s",label);
        }
        textcount++;
    }
    else if (line[3][0] == '\0')
    {
        strcpy(opcode, line[1]);
        strcpy(address, line[0]);
        strcpy(label, line[2]);
        // printf("%s-%s-%s\n", opcode, address, label);
        writeToTextRecord(opcode, address, label, f);
    }
    else if(line[3][0] != '\0'){
        strcpy(opcode,line[2]);
        strcpy(address,line[0]);
        strcpy(label,line[3]);
        // printf("%s-%s-%s\n",opcode,address,label);
        writeToTextRecord(opcode,address,label,f);
    }
    else{
        printf("Error in program! please do the needful");
    }
    return 1;
}
void main()
{
    FILE *f;
    char *line = (char *)malloc(sizeof(char) * 50);
    f = fopen("intermediate.txt", "r");
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
                if (!secondPass(split_code,fo))
                {
                    break;
                }
            }
            // printf("%s-%s-%s-%s\n", split_code[0], split_code[1], split_code[2],split_code[3]);
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