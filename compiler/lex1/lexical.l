%{
int count=0;
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* {fprintf(yyout, "<%s>", yytext);count++;printf("\t identifier : %s\n",
 yytext);}
 [-+*/=%] {fprintf(yyout, "<%s>", yytext);count++;printf("\t operator:%s", yytext);}
[ \n\t]+ {}
[0-9][0-9]*.[0-9]+[1-9]+(E[+-]?[0-9]+)? {fprintf(yyout, "<%s>", yytext);count++;printf("\t  floating point : %s\n",
 yytext);}
 [1-9][0-9]* {fprintf(yyout, "<%s>", yytext);count++;printf("\t integer  : %s\n",
yytext);}
0+[1-9]*|[0-9][0-9]*.00+ {printf("\t invalid:%s",yytext);}
[0-9]*"."[0-9]+ {fprintf(yyout, "<%s>", yytext);count++;printf("\t floating point : %s\n",
 yytext);}

[(){}|,:] {fprintf(yyout, "<%s>", yytext);count++;printf("\t seperators:%s\n",
yytext);}
%%
int yywrap(){}
int main()
{ char c;
FILE *f1,*f2;
char filename[50];
f1 = fopen("input.txt","r");
f2 = fopen("output.txt","w+");
yyin = f1;
yyout=f2;
yylex();
printf("\n total no. of tokens = %d\n",count);
}
