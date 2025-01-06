#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50
#define MAX_INPUT_SIZE 50
// Define stack and input buffers
char stack[MAX_STACK_SIZE];
char input[MAX_INPUT_SIZE];
// Grammar symbols for simplicity
#define E 0
#define T 1
#define F 2
#define PLUS 3
#define STAR 4
#define LPAREN 5
#define RPAREN 6
#define ID 7
#define END 8
// Grammar rules
// E → E + T
// E → T
// T → T * F
// T → F
// F → (E)
// F → id
// Action table (action[state][symbol])
int action[5][9] = {
// E T F + * ( ) id $
{ 0, 1, 2, 3, 4, 5, -1, 6, 0 }, // state 0
{ -1, -1, -1, 7, 0, -1, -1, -1, -1 }, // state 1
{ 8, 2, 2, 3, 4, 5, -1, 6, 0 }, // state 2
{ -1, -1, -1, 7, 0, -1, -1, -1, -1 }, // state 3
{ -1, -1, 2, 3, 4, 5, -1, 6, 0 }, // state 4
};
// Parsing the input
void parse(char *input) {
int top = 0, i = 0;
stack[top] = '0'; // Push the initial state (state 0)
char symbol;
while (input[i] != '$') {
symbol = input[i];
// Get the action from the table
int state = stack[top] - '0';
int action_code = action[state][symbol - '0'];
if (action_code == -1) {
printf("Error: Invalid input at position %d\n", i);
return;
}
// Shift operation
if (action_code >= 0) {
printf("Shift: symbol = %c, new state = %d\n", symbol, action_code);
stack[++top] = action_code + '0'; // Push the new state
i++;
}
}
}
int main() {
// Input string to parse
printf("Enter input string: ");
scanf("%s", input);
strcat(input, "$"); // Append end symbol
// Call the parser
parse(input);
return 0;
}