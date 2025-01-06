#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
// Operator precedence levels
int get_precedence(char op) {
switch (op) {
case '+':
case '-': return 1;
case '*':
case '/': return 2;
default: return 0;
}
}
// Evaluates a simple expression with two operands and an operator
int apply_operator(int a, int b, char op) {
switch (op) {
case '+': return a + b;
case '-': return a - b;
case '*': return a * b;
case '/':
if (b != 0) return a / b;
printf("Error: Division by zero\n");
exit(1);
default:
printf("Error: Unknown operator %c\n", op);
exit(1);
}
}
// Parses and evaluates the expression using operator precedence
int evaluate_expression(const char *expression) {
int values[MAX]; // Stack to store integers (operands)
char operators[MAX]; // Stack to store operators
int values_top = -1, operators_top = -1;
for (int i = 0; expression[i] != '\0'; i++) {
char token = expression[i];
if (isdigit(token)) {
// Read the full number (handle multi-digit numbers)
int value = 0;
while (i < strlen(expression) && isdigit(expression[i])) {
value = value * 10 + (expression[i] - '0');
i++;
}
i--; // Step back to process the next character
values[++values_top] = value;
printf("Added %d to values stack\n", value);
}
else if (token == '+' || token == '-' || token == '*' || token == '/') {
// Resolve all operators with higher or equal precedence
while (operators_top != -1 &&
get_precedence(operators[operators_top]) >= get_precedence(token)) {
int b = values[values_top--];
int a = values[values_top--];
char op = operators[operators_top--];
int result = apply_operator(a, b, op);
values[++values_top] = result;
printf("Applied %c: %d %c %d = %d\n", op, a, op, b, result);
}
// Push the current operator to operators stack
operators[++operators_top] = token;
printf("Added %c to operators stack\n", token);
}
else if (token != ' ') { // Ignore spaces
printf("Unexpected character: %c\n", token);
exit(1);
}
}
// Evaluate remaining operators
while (operators_top != -1) {
int b = values[values_top--];
int a = values[values_top--];
char op = operators[operators_top--];
int result = apply_operator(a, b, op);
values[++values_top] = result;
printf("Applied %c: %d %c %d = %d\n", op, a, op, b, result);
}
// Final result is the last value on the values stack
return values[values_top];
}
int main() {
char expression[MAX];
printf("Enter an expression: ");
fgets(expression, MAX, stdin);
// Remove newline character from fgets
size_t len = strlen(expression);
if (expression[len - 1] == '\n') {
expression[len - 1] = '\0';
}
int result = evaluate_expression(expression);
printf("Result: %d\n", result);
return 0;
}