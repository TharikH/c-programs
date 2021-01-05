#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void writeToIntermediate(char *line)
{
    FILE *f;
    f = fopen("intermediate.txt", "a");
    fprintf(f, "%s\n", line);
    fclose(f);
}
void writeToSymbol(char *label, char *addr)
{
    FILE *f, *w;
    char *line = (char *)malloc(sizeof(char) * 12), error[] = "duplicate error";
    char **split = (char **)malloc(sizeof(char *) * 2);
    split[0] = (char *)malloc(sizeof(char) * 6);
    split[1] = (char *)malloc(sizeof(char) * 6);
    f = fopen("symbol.txt", "r");
    while (fgets(line, 12, f) != NULL)
    {
        split_by_delimeter(line, split, ' ');
        if (strcasecmp(split[1], label) == 0)
        {
            writeToIntermediate(error);
            fclose(f);
            return;
        }
    }
    fclose(f);
    w = fopen("symbol.txt", "a");
    fprintf(w, "%s\t%s\n", label, addr);
    fclose(w);
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
int isValidOpcode(char *opcode)
{
    FILE *f;
    int temp = 0;
    char *line = (char *)malloc(sizeof(char) * 20), error[] = "not valid opcode error";
    f = fopen("opcode.txt", "r");
    while (fgets(line, 20, f) != NULL)
    {
        char **split = (char **)malloc(sizeof(char *) * 3);
        split[0] = (char *)malloc(sizeof(char) * 6);
        split[1] = (char *)malloc(sizeof(char) * 6);
        split[2] = (char *)malloc(sizeof(char) * 6);
        // printf("check -- %s",line);
        split_by_delimeter(line, split, ' ');
        if (strcasecmp(split[0], opcode) == 0)
        {
            fclose(f);
            printf("check -- %s-\n", split[2]);
            sscanf(split[2], "%d", &temp);

            return temp;
        }
    }
    writeToIntermediate(error);
    return 0;
}
int pseudoCode(char **split)
{
    int size;
    if (strcasecmp(split[1], "RESW") == 0)
    {
        sscanf(split[2], "%d", &size);
        return 3 * size;
    }
    else if (strcasecmp(split[1], "WORD") == 0)
    {
        return 3;
    }
    else if (strcasecmp(split[1], "RESB") == 0)
    {
        sscanf(split[2], "%d", &size);
        return size;
    }
    else if (strcasecmp(split[1], "BYTE") == 0)
    {
        return 1;
    }
    else if (strcmp(split[1], "BASE") == 0)
    {
        return 0;
    }
    else if (strcmp(split[1], "NOBASE") == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int firstPass(char **split, int *locctr)
{
    char *addr = (char *)malloc(sizeof(char)), *line = (char *)malloc(sizeof(char) * 36);
    int isindex = 0, pseudo_add, opsize;
    if (strcasecmp(split[1], "START") == 0)
    {
        if (split[2][0] == '\0')
        {
            (*locctr) = 0;
        }
        else
        {
            sscanf(split[2], "%d", locctr);
        }
        addr = paddingZero(decToHex(*locctr));
    }
    else
    {
        if (strcasecmp(split[1], "END") == 0)
        {
            addr = paddingZero(decToHex(*locctr));
            if (!(split[2][0] > '0' && split[2][0] < '9'))
            {
                // split[2][0] = '\0';
                strcpy(split[2], "\0");
            }
            sprintf(line, "%s\t%s\t%s\t%s", addr, split[0], split[1], split[2]);
            // printf("%s\n",split[2]);
            // printf("%s-%s-%s",split[0],split[1],split[2]);
            writeToIntermediate(line);
            char locstring[10];
            sprintf(locstring, "count:%s", paddingZero(decToHex(*locctr)));
            writeToIntermediate(locstring);
            return 0;
        }
        else if ((pseudo_add = pseudoCode(split)) >= 0)
        {
            addr = paddingZero(decToHex(*locctr));
            (*locctr) += pseudo_add;
        }
        else if ((opsize = isValidOpcode(split[1])) != 0)
        {
            if (split[2][0] == '\0')
            {
                printf("hello");
            }
            addr = paddingZero(decToHex(*locctr));
            (*locctr) += opsize;
        }
    }
    if (split[0][0] != '\0')
    {
        writeToSymbol(split[0], addr);
    }
    sprintf(line, "%s\t%s\t%s\t%s", addr, split[0], split[1], split[2]);
    writeToIntermediate(line);
    free(addr);
    return 1;
}
void main()
{
    FILE *f;
    int locctr = 0;
    char *line = (char *)malloc(sizeof(char) * 40);
    f = fopen("source.txt", "r");
    while (fgets(line, 40, f) != NULL)
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
            writeToIntermediate(line);
        }
        else
        {
            if (!firstPass(split_code, &locctr))
            {
                break;
            }
        }
        printf("%s-%s-%s\n", split_code[0], split_code[1], split_code[2]);
        free(split_code);
        // printf("%s ",line);
    }
    fclose(f);
}
