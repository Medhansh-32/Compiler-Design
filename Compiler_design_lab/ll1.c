#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char lookahead;
int pos = 0;
char input[100];
// Function to match and advance the lookahead
void match(char t) {
if (lookahead == t) {
printf(" Matched '%c'\n", t);
lookahead = input[++pos];
} else {
printf("Syntax error: Expected '%c' but found '%c'\n", t, lookahead);
exit(1);
}
}
// Forward declarations for grammar functions
void E();
void E_prime();
void T();
void T_prime();
void F();
// Grammar rule functions with debug outputs
void E() {
printf("Entering E\n");
T();
E_prime();
printf("Exiting E\n");
}
void E_prime() {
while (lookahead == '+' || lookahead == '-') { // Simplified
printf("E' found '%c'\n", lookahead);
match(lookahead);
T();
}
}
void T() {
printf("Entering T\n");
F();
T_prime();
printf("Exiting T\n");
}

void T_prime() {
while (lookahead == '*' || lookahead == '/') { // Simplified
printf("T' found '%c'\n", lookahead);
match(lookahead);
F();
}
}
void F() {
printf("Entering F\n");
if (isdigit(lookahead)) {
printf("F found number ");
while (isdigit(lookahead)) {
printf("%c", lookahead);
match(lookahead);
}
printf("\n");
} else if (lookahead == '(') {
match('(');
E();
match(')');
} else {
printf("Syntax error: Unexpected character '%c'\n", lookahead);
exit(1);
}
printf("Exiting F\n");
}
int main() {
printf("Enter an expression: ");
scanf("%s", input);
lookahead = input[pos];
E();
if (lookahead == '\0') {
printf("Parsing successful\n");
} else {
printf("Syntax error at end of input\n");
}
return 0;
}