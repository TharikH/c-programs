%{
int count=0;
%}

%%
int|void {fprintf(yyout, "<keyword,%s>\n", yytext);count++;printf("keyword:%s\n", yytext);}


[a-zA-Z_][a-zA-Z0-9_.$]* {fprintf(yyout, "<identifier,%s>\n", yytext);count++;printf("identifier : %s\n",yytext);}


[-+*/=%&] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}

[+][+] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}
[-][-] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}
[+][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}
[*][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}
[-][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}
[/][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}

[/][/][a-zA-Z_][a-zA-Z0-9_.$]* {}

["][0-9a-zA-Z]*.[a-zA-Z]*["]|["][0-9a-zA-Z% ]*["] {fprintf(yyout, "<string,%s>\n", yytext);count++;printf("operator:%s\n", yytext);}

[^a-zA-Z_][^a-zA-Z0-9_]*[*] {fprintf(yyout, "<pointer,%s>\n", yytext);count++;printf("pointer:%s\n", yytext);}

[ \n\t]+ {}

[0-9][0-9]*.[0-9]+[1-9]+ {fprintf(yyout, "<float,%s>\n", yytext);count++;printf("floating point : %s\n",yytext);}

[1-9][0-9]* {fprintf(yyout, "<int,%s>\n", yytext);count++;printf("integer : %s\n",yytext);}

0+[1-9]*|[0-9][0-9]*.00+ {printf("\t invalid:%s",yytext);}

[(){}|,:<>;#] {fprintf(yyout, "<separator,%s>\n", yytext);count++;printf("seperators:%s\n",yytext);}

%%
int yywrap(){}
int main()
{
FILE *f1,*f2;
f1 = fopen("input.c","r");
f2 = fopen("output.txt","w+");
yyin = f1;
yyout=f2;
yylex();
printf("total no. of tokens = %d\n",count);
}
