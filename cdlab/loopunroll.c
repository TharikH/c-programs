#include <stdio.h>
void printHello1()
{  
	for(int i=0;i<3;i++)
		printf("HELLO\n");	
}
void printHello2()
{
    printf("HELLO");
    printf("\nHELLO");
    printf("\nHELLO");


}

void main()
{
    int d;
    char ch;
    printf("\n1. Loop Roll\n2. Loop UnRoll\n");
    do
    {
        printf("\nEnter ur choice\n");
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            printHello1();
            break;
        case '2':
            printHello2();
            break;
        default:
            printf("\n Wrong Choice\n");
        }
        printf("\nDo you want to continue Press 1 ?\n");
        scanf("%d", &d);
    } while (d == 1);
}