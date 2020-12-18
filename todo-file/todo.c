#include <stdio.h>
#include <string.h>

FILE *file;
void help_display()
{
    printf(""
           "Usage :-\n"
           "$ ./todo add \"todo item\"  # Add a new todo\n"
           "$ ./todo ls               # Show remaining todos\n"
           "$ ./todo del NUMBER       # Delete a todo\n"
           "$ ./todo done NUMBER      # Complete a todo\n"
           "$ ./todo help             # Show usage\n"
           "$ ./todo report           # Statistics\n");
}
int commandCodeGenerator(char *command)
{
    // printf("%s",command);
    if (strcmp(command, "add") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "ls") == 0)
    {
        return 2;
    }
    else if (strcmp(command, "del") == 0)
    {
        return 3;
    }
    else if (strcmp(command, "done") == 0)
    {
        return 4;
    }
    else if (strcmp(command, "help") == 0)
    {
        return 5;
    }
    else if (strcmp(command, "report") == 0)
    {
        return 6;
    }
    else
    {
        return 0;
    }
}
void addTodo(int count, char *argv[])
{
    // for(int i=1;i<count;i++){
    //     printf("%s",argv[i]);
    // }
    if (count < 3)
    {
        printf("Error: Missing todo string. Nothing added!\n");
    }
    else
    {
        file = fopen("todo.txt", "a");
        for (int i = 2; i < count; i++)
        {
            fprintf(file, "%s\n0\n", argv[i]);
            printf("Added todo: \"%s\"\n", argv[i]);
        }
        fclose(file);
    }
}
int fileCount()
{
    int count = 0, i = 0;
    file = fopen("todo.txt", "r");
    char str[60];
    if (file)
    {
        while (fgets(str, 60, file))
        {
            if (i % 2 == 1 && strcmp(str, "0\n")==0)
            {
                count++;
            }
            i++;
        }
    }
    // printf("count: %d",count);
    return count;
}
void listTodo()
{
    int count = fileCount();
    // printf("%d",count);
    if (count > 0)
    {
        file = fopen("todo.txt", "r");
        char str[60], complete[3];
        if (file)
        {
            while (fgets(str, 60, file))
            {
                // printf("---%s",str);
                fgets(complete, 3, file);
                // printf("---%s",str);
                if (strcmp(complete, "0\n") == 0)
                {
                    printf("[%d] %s", count, str);
                    count--;
                }
                
            }
            fclose(file);
        }
    }
    else
    {
        printf("All Todos completed");
    }
}
void deleteTodo(int count, char *argv[])
{
    if (count != 3)
    {
        printf("error\n");
    }
    else
    {
        int data = argv[2][0] - '0', num = fileCount(),j=0,line,k=0;
        file = fopen("todo.txt", "r+");
        FILE *f=fopen("todo.txt","r+");
        char str[60],buf[60], complete[3];
        if (file)
        {
            while (fgets(str, 60, file))
            {
                k++;
                // printf("---%s",str);
                fgets(complete, 3, file);
                // printf("---%s",str);
                if (strcmp(complete, "0\n") == 0)
                {
                    char c[5];
                    strcpy(c,"\0");
                    printf("%d %d %d\n",data,num,j);
                    if (data == num-j)
                    {
                        line=k;
                        break;
                    }
                    j++;
                }
            }
            fclose(f);
            fclose(file);
        }
        file=fopen("todo.txt","r");
        f=fopen("temp.txt","w");
        k=0;
    while (!feof(file)) 
        {
            strcpy(str, "\0");
            fgets(str, 60, file);
            if (!feof(file)) 
            {
                k++;
                /* skip the line at given line number */
                if (k != line) 
                {
                    fprintf(f, "%s", str);
                }else{
                    fgets(str,60,file);
                }
            }
        }
        fclose(file);
        fclose(f);
        remove("todo.txt");  		// remove the original file 
        rename("temp.txt", "todo.txt");

    }
}
void doneTodo(int count, char *argv[])
{
    if (count != 3)
    {
        printf("error\n");
    }
    else
    {
        int data = argv[2][0] - '0', num = fileCount(),j=0;
        file = fopen("todo.txt", "r+");
        FILE *f=fopen("todo.txt","r+");
        char str[60],buf[60], complete[3];
        if (file)
        {
            while (fgets(str, 60, file))
            {
                // printf("---%s",str);
                fgets(complete, 3, file);
                // printf("---%s",str);
                if (strcmp(complete, "0\n") == 0)
                {
                    fgets(buf, 60, f);
                    char c[]="1";
                    printf("%d %d %d\n",data,num,j);
                    if (data == num-j)
                    {
                        fprintf(f,"%s", c);
                        printf("Marked as completed");
                        break;
                    }
                    j++;
                }else{
                    fgets(buf, 60, f);
                }
                fgets(buf,60,f);
            }
            fclose(f);
            fclose(file);
        }
    }
}
int totalCount(){
int count =0;
file=fopen("todo.txt","r");
for (char c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
return count/2;
}
void reportTodo(){
int incomplete=fileCount();
int total=totalCount();
printf("completed :%d (%d%%)\nincomplete :%d(%d%%)\n",total-incomplete,(total-incomplete)*100/total,incomplete,incomplete*100/total);
}
int main(int argc, char *argv[])
{
    int commandCode = 0;
    if (argc == 1)
    {
        help_display();
    }
    else
    {
        commandCode = commandCodeGenerator(argv[1]);
        switch (commandCode)
        {
        case 0:
            printf("Wrong command!\n");
            goto help;
        case 1:
            addTodo(argc, argv);
            break;
        case 2:
            if (argc > 2)
            {
                goto help;
            }
            listTodo();
            break;
        case 3:
            deleteTodo(argc, argv);
            break;
        case 4:
            doneTodo(argc, argv);
            break;
        case 5:
        help:
            help_display();
            break;
        case 6:
            reportTodo();
            break;
        }
    }

    return 0;
}
