#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 100
// Function to check and print identifiers
void checkIdentifier(const char *input, int *index) {
int i = 0;
char identifier[MAX_LENGTH] = {0};
while (input[*index] && (isalnum(input[*index]) || input[*index] == '_')) {
identifier[i++] = input[*index];
(*index)++;
}
identifier[i] = '\0';
if (i > 0) {
printf("Identifier: %s\n", identifier);
}
}
// Function to check and print constants (numeric literals)
void checkConstant(const char *input, int *index) {
int i = 0;
char constant[MAX_LENGTH] = {0};
while (input[*index] && (isdigit(input[*index]) || input[*index] == '.')) {
constant[i++] = input[*index];
(*index)++;
}
constant[i] = '\0';
if (i > 0) {
printf("Constant: %s\n", constant);
}
}
// Function to check and print comments (both single-line and multi-line)
void checkComment(const char *input, int *index) {
if (strncmp(&input[*index], "//", 2) == 0) {
printf("Single-line comment: ");
while (input[*index] && input[*index] != '\n') {
putchar(input[*index]);
(*index)++;
}
putchar('\n');
} else if (strncmp(&input[*index], "/*", 2) == 0) {
printf("Multi-line comment: ");
(*index) += 2; // Skip "/*"
while (input[*index] && strncmp(&input[*index], "*/", 2) != 0) {
putchar(input[*index]);
(*index)++;
}
if (input[*index]) (*index) += 2; // Skip "*/"
putchar('\n');
}
}
// Function to check and print operators
void checkOperator(const char *input, int *index) {
char operator[3] = {input[*index], input[*index + 1], '\0'};
if (operator[0] == '+' || operator[0] == '-' || operator[0] == '*' || operator[0] == '/' ||
operator[0] == '%' || operator[0] == '=' || operator[0] == '<' || operator[0] == '>') {
if ((operator[0] == '+' && operator[1] == '+') || (operator[0] == '-' && operator[1] == '-')) {
printf("Operator: %s\n", operator);
(*index)++;
} else if (operator[0] == '=' && operator[1] == '=') {
printf("Operator: ==\n");
(*index)++;
} else if (operator[0] == '!' && operator[1] == '=') {
printf("Operator: !=\n");
(*index)++;
} else if (operator[0] == '<' && operator[1] == '=') {
printf("Operator: <=\n");
(*index)++;
} else if (operator[0] == '>' && operator[1] == '=') {
printf("Operator: >=\n");
(*index)++;
} else if ((operator[0] == '+' && operator[1] == '=') || (operator[0] == '-' && operator[1] == '=')) {
printf("Operator: %s=\n", operator);
(*index)++;
} else {
printf("Operator: %c\n", operator[0]);
}
}
(*index)++;
}
// Function to process input and classify tokens
void processInput(const char *input) {
int i = 0;
while (input[i]) {
if (isspace(input[i]) || input[i] == ';') {
i++;
} else if (isalpha(input[i]) || input[i] == '_') {
checkIdentifier(input, &i);
} else if (isdigit(input[i])) {
checkConstant(input, &i);
} else if (input[i] == '/' && (input[i + 1] == '/' || input[i + 1] == '*')) {
checkComment(input, &i);
} else {
checkOperator(input, &i);
}
}
}

int main() {
char input[MAX_LENGTH];
while (1) {
printf("\nEnter code (or type 'exit' to quit): ");
if (fgets(input, sizeof(input), stdin) == NULL) {
printf("Error reading input.\n");
continue;
}
input[strcspn(input, "\n")] = '\0';
if (strcmp(input, "exit") == 0) {
printf("Exiting.\n");
break;
}
processInput(input);
}
return 0;
}