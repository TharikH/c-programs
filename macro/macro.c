#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SOURCECODE
{
    char label[30];
    char opcode[30];
    char operand[30];
} sourceCode[100];
int iSourceCount = 0;
struct DEFTAB
{
    char label[30];
    char opcode[30];
    char operand[30];
} defTab[100];
int idefTabCount = 0;
int level =0;
struct NAMTAB
{
    char name[30];
    int start;
    int end;
} nameTab[100];
struct ARGTAB
{
    char argument[100][50];
} argtab;
int iNameCount = 0;
FILE *macroSource;
int expanding = 0;
int iCount;
void DEFINE()
{
    int iCount1 = 0, iArg = 0, flag = 0, iCount2 = 0;
    char arguments[10][30], arg[10];
    FILE *defTable;
    strcpy(nameTab[iNameCount].name, sourceCode[iCount].label);
    nameTab[iNameCount].start = idefTabCount;
    strcpy(defTab[idefTabCount].label, sourceCode[iCount].label);
    strcpy(defTab[idefTabCount].opcode, sourceCode[iCount].opcode);
    strcpy(defTab[idefTabCount++].operand, sourceCode[iCount].operand);
    while (sourceCode[iCount].operand[iCount1] != '\0')
    {
        arguments[iArg][iCount2++] = sourceCode[iCount].operand[iCount1++];
        if (sourceCode[iCount].operand[iCount1] == ',' || sourceCode[iCount].operand[iCount1] == '\0')
        {
            arguments[iArg++][iCount2] = '\0';
            iCount2 = 0;
            iCount1++;
        }
    }
    while (level > 0)
    {
        iCount++;
        flag = 0;
        for (iCount1 = 0; iCount1 < iArg; iCount1++)
        {
            if (strcmp(arguments[iCount1], sourceCode[iCount].operand) == 0)
            {
                strcpy(defTab[idefTabCount].label, sourceCode[iCount].label);
                strcpy(defTab[idefTabCount].opcode, sourceCode[iCount].opcode);
                strcpy(defTab[idefTabCount].operand, "?");
                // itoa(iCount1 + 1, arg, 10);
                sprintf(arg,"%d",iCount1);
                strcat(defTab[idefTabCount++].operand, arg);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            strcpy(defTab[idefTabCount].label, sourceCode[iCount].label);
            strcpy(defTab[idefTabCount].opcode, sourceCode[iCount].opcode);
            strcpy(defTab[idefTabCount++].operand, sourceCode[iCount].operand);
        }
        if (strcmp(sourceCode[iCount].opcode, "MACRO") == 0)
        {
            level++;
            DEFINE();
        }
        else if (strcmp(sourceCode[iCount].opcode, "MEND") == 0)
        {
            level--;
        }
    }
    nameTab[iNameCount++].end = idefTabCount;
    defTable = fopen("DEFTAB.txt", "w");
    // fprintf(defTable, "\n\nDEFINITION TABLE\n\n");
    for (iCount1 = 0; iCount1 < idefTabCount; iCount1++)
    {
        fprintf(defTable, "%s\t%s\t%s\n", defTab[iCount1].label, defTab[iCount1].opcode, defTab[iCount1].operand);
    }
}
FILE *result;
void EXPAND(int index)
{
    int iCount1 = 0, iArg = 0, iCount2 = 0;
    char argPoint[10];
    expanding = 1;
    while (sourceCode[iCount].operand[iCount1] != '\0')
    {
        argtab.argument[iArg][iCount2++] = sourceCode[iCount].operand[iCount1++];
        if (sourceCode[iCount].operand[iCount1] == ',' || sourceCode[iCount].operand[iCount1] == '\0')
        {
            argtab.argument[iArg++][iCount2] = '\0';
            iCount2 = 0;
            iCount1++;
        }
    }
    fprintf(result, "%s\t%s\t%s\n", sourceCode[iCount].label, sourceCode[iCount].opcode, sourceCode[iCount].operand);
    for (iCount1 = nameTab[index].start + 1; iCount1 < nameTab[index].end; iCount1++)
    {
        fprintf(result, "%s\t%s\t", defTab[iCount1].label, defTab[iCount1].opcode);
        if (defTab[iCount1].operand[0] == '?')
        {
            argPoint[0] = defTab[iCount1].operand[1];
            argPoint[1] = '\0';
            fprintf(result, "%s\n", argtab.argument[atoi(argPoint)]);
            continue;
        }
        fprintf(result, "%s\n", defTab[iCount1].operand);
    }
    expanding = 0;
}
int main()
{
    char label[30], opcode[30], operand[30];
    int flag = 1, iCount1;
    result = fopen("MacroOutput.txt", "w");
    macroSource = fopen("macro.txt", "r");
    while (strcmp(opcode, "END"))
    {
        fscanf(macroSource, "%s %s %s", label, opcode, operand);
        strcpy(sourceCode[iSourceCount].label, label);
        strcpy(sourceCode[iSourceCount].opcode, opcode);
        strcpy(sourceCode[iSourceCount++].operand, operand);
    }
    fclose(macroSource);
    expanding = 0;
    for (iCount = 0; iCount < iSourceCount; iCount++)
    {
        flag = 1;
        for (iCount1 = 0; iCount1 < iNameCount; iCount1++)
        {
            if (!strcmp(sourceCode[iCount].opcode, nameTab[iCount1].name))
            {
                EXPAND(iCount1);
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            if (!strcmp(sourceCode[iCount].opcode, "MACRO"))
            {
            printf("helo");
            level++;
                DEFINE();
            }
            else
            {
                fprintf(result, "%s\t%s\t%s\n", sourceCode[iCount].label, sourceCode[iCount].opcode, sourceCode[iCount].operand);
            }
        }
    }
    fclose(result);
    return 1;
}
