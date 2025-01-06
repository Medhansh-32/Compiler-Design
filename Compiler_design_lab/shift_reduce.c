#include <stdio.h>
#include <string.h>
#define MAX 100
// Stack to hold the parsed symbols
char stack[MAX];
int top = -1; // Top of the stack
// Function to push an element onto the stack
void push(char c) {
if (top < MAX - 1) {
stack[++top] = c;
}
}
// Function to pop an element from the stack
char pop() {
if (top >= 0) {
return stack[top--];
}
return '\0';
}
// Function to print the current stack
void print_stack() {
printf("Stack: ");
for (int i = 0; i <= top; i++) {
printf("%c ", stack[i]);
}
printf("\n");
}
// Function to implement the Shift-Reduce parsing algorithm
void shift_reduce_parse(char *input) {
int i = 0; // Pointer to input string
printf("Input string: %s\n", input);
// Start parsing the input string
while (input[i] != '\0' || top > 0) {
// Perform Shift operation (shift the next symbol to the stack)
if (input[i] != '\0') {
push(input[i]);
printf("Shift: ");
print_stack();

i++;
}
// Perform Reduce operation
while (top > 0) {
if (stack[top] == ')' && stack[top - 1] == '(') { // Check for S → ( L )
pop(); // Pop ')'
pop(); // Pop '('
push('S'); // Push 'S'
printf("Reduce: S -> ( L )\n");
print_stack();
} else if (stack[top] == ',' && stack[top - 1] == 'a') { // Check for L → L , S
pop(); // Pop 'a'
pop(); // Pop ','
pop(); // Pop 'L'
push('L'); // Push 'L'
printf("Reduce: L -> L , S\n");
print_stack();
} else if (stack[top] == 'a') { // Check for L → S or S → a
pop(); // Pop 'a'
push('L'); // Push 'L'
printf("Reduce: L -> S\n");
print_stack();
} else {
break; // No more reductions possible
}
}
}
// Final check if the entire string has been reduced to S
if (top == 0 && stack[top] == 'S') {
printf("Input string is accepted.\n");
} else {
printf("Syntax error: Unable to reduce to start symbol S.\n");
}
}
int main() {
char input[MAX];
// Input the string
printf("Enter the input string (e.g., (a,a)): ");
fgets(input, sizeof(input), stdin);
// Remove the newline character at the end of the input
input[strcspn(input, "\n")] = '\0';
// Call the shift-reduce parser
shift_reduce_parse(input);
return 0;
}