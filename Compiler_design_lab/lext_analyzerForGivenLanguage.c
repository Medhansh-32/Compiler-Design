#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
// Function to check if a string is a keyword
int isKeyword(char *word) {
const char *keywords[] = {"int", "float", "if", "else", "while", "return", "void", "char", "for", "do"};
for (int i = 0; i < 10; i++) {
if (strcmp(word, keywords[i]) == 0) {
return 1;
}
}
return 0;
}
// Function to check if a string is an operator
int isOperator(char ch) {
char operators[] = "+-*/=%";
for (int i = 0; i < strlen(operators); i++) {
if (ch == operators[i]) {
return 1;
}
}
return 0;
}
// Main function to analyze tokens
void lexicalAnalyzer(char *input) {
char buffer[MAX];
int i = 0, j = 0;
printf("Lexical Analysis Output:\n");
printf("-------------------------\n");
while (input[i] != '\0') {
// Ignore redundant spaces, tabs, and newlines
if (isspace(input[i])) {
i++;
continue;
}
// Recognize keywords, identifiers, and constants
if (isalnum(input[i]) || input[i] == '_') {
buffer[j++] = input[i];
} else {
if (j > 0) {
buffer[j] = '\0';
if (isKeyword(buffer)) {
printf("Keyword: %s\n", buffer);
} else if (isdigit(buffer[0])) {
printf("Constant: %s\n", buffer);
} else {
printf("Identifier: %s\n", buffer);
}
j = 0;
}
// Recognize operators
if (isOperator(input[i])) {
printf("Operator: %c\n", input[i]);
}
// Recognize single-line comments
if (input[i] == '/' && input[i + 1] == '/') {
printf("Comment: ");
while (input[i] != '\0' && input[i] != '\n') {
putchar(input[i++]);
}
printf("\n");
}
// Recognize multi-line comments
if (input[i] == '/' && input[i + 1] == '*') {
printf("Comment: ");
i += 2;
while (input[i] != '\0' && !(input[i] == '*' && input[i + 1] == '/')) {
putchar(input[i++]);
}
if (input[i] == '*' && input[i + 1] == '/') {
i += 2;
printf("*/\n");
}
}
}
i++;
}
// Final check for a token in the buffer
if (j > 0) {
buffer[j] = '\0';
if (isKeyword(buffer)) {
printf("Keyword: %s\n", buffer);
} else if (isdigit(buffer[0])) {
printf("Constant: %s\n", buffer);
} else {
printf("Identifier: %s\n", buffer);
}
}
}
