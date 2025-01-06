%{
#include <stdio.h>
%}
%%
"int"|"float"|"if"|"else"|"while"|"return"|"void"|"char" {
printf("Keyword: %s\n", yytext);
}
[a-zA-Z_][a-zA-Z0-9_]* {
printf("Identifier: %s\n", yytext);
}
[0-9]+ {
printf("Constant: %s\n", yytext);
}
"+"|"-"|"*"|"/"|"=" {
printf("Operator: %s\n", yytext);
}
"//".* {
printf("Single-line Comment: %s\n", yytext);
}
"/*"([^*]|\*+[^*/])*\*+"/" {
printf("Multi-line Comment\n");
}
[ \t\n] ; /* Ignore whitespace */
. {
printf("Unknown token: %s\n", yytext);
}
%%
int main() {
printf("Enter code to analyze (Press Ctrl+D to stop):\n");
yylex(); // Start lexical analysis
return 0;
}