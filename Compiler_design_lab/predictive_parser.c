#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
char input[100]; // Input expression
int index = 0; // Current position in input
// Function to get the next character in the input
char lookahead() {
return input[index];
}
// Match the current character with the expected character
void match(char expected) {
if (lookahead() == expected) {
index++; // Move to the next character in the input
} else {
printf("Syntax error: Expected '%c' but found '%c'\n", expected, lookahead());
exit(1); // Exit if the expected character is not found
}
}
// F → id | ( E )
void F() {
if (isalpha(lookahead())) {
printf("Matched id\n");
match(lookahead()); // Match identifier
} else if (lookahead() == '(') {
match('('); // Match '('
E(); // Parse the expression inside parentheses
match(')'); // Match ')'
} else {
printf("Syntax error in F: Unexpected symbol '%c'\n", lookahead());
exit(1);
}
}
// T → F | T * F
void T() {
F(); // Parse the first factor
while (lookahead() == '*') { // If the next token is a multiplication operator
printf("Matched *\n");
match('*');

F(); // Parse the next factor
}
}
// E → T | E + T
void E() {
T(); // Parse the first term
while (lookahead() == '+') { // If the next token is an addition operator
printf("Matched +\n");
match('+');
T(); // Parse the next term
}
}
// Main function
int main() {
printf("Enter an expression: ");
fgets(input, sizeof(input), stdin);
printf("Parsing the expression...\n");
E(); // Start parsing from the start symbol (E)
if (lookahead() == '\0') {
printf("Expression parsed successfully.\n");
} else {
printf("Syntax error: Unexpected symbol '%c'\n", lookahead());
}
return 0;
}
