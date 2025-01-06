#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_SYMBOLS 100
typedef struct {
char identifier[50];
char scope[10];
char value[50];
char type[10];
} Symbol;
Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;
void addSymbol(char *identifier, char *scope, char *value, char *type) {
if (symbolCount >= MAX_SYMBOLS) return;
strcpy(symbolTable[symbolCount].identifier, identifier);
strcpy(symbolTable[symbolCount].scope, scope);
strcpy(symbolTable[symbolCount].value, value);
strcpy(symbolTable[symbolCount].type, type);
symbolCount++;
}
int isIdentifier(char *str) {
if (!isalpha(str[0]) && str[0] != '_') return 0;
for (int i = 1; str[i]; i++) {
if (!isalnum(str[i]) && str[i] != '_') return 0;
}
return 1;
}
int symbolExists(char *identifier, char *scope) {
for (int i = 0; i < symbolCount; i++) {
if (strcmp(symbolTable[i].identifier, identifier) == 0 && strcmp(symbolTable[i].scope, scope) == 0) return 1;
}
return 0;
}
char* detectType(char *value) {
if (value[0] == '\'' && value[2] == '\'') return "char";
if (value[0] == '\"' && value[strlen(value) - 1] == '\"') return "string";
if (strchr(value, '.') != NULL) return "double";
if (isdigit(value[0]) || value[0] == '-' && isdigit(value[1])) return "int";
return "unknown";
}
void IdentifierCheck(char *str, char *scope) {
char identifier[50], value[50], type[10];
int i = 0, j = 0;
// Skip leading spaces
while (isspace(str[i])) i++;
// Extract identifier
while (str[i] && str[i] != '=' && str[i] != '}' && !isspace(str[i])) {
identifier[j++] = str[i++];
}
identifier[j] = '\0';
// Check if the identifier is valid
if (!isIdentifier(identifier)) {
return;
}
// Skip spaces
while (isspace(str[i])) i++;
// Check for assignment
if (str[i] == '=') {
i++; // Skip '='
while (isspace(str[i])) i++; // Skip spaces
// Extract value
j = 0;
while (str[i] && str[i] != ';' && str[i] != '}' && str[i] != '\0') {
value[j++] = str[i++];
}
value[j] = '\0';
// Detect type based on value
strcpy(type, detectType(value));
// Add symbol if it doesn't exist
if (!symbolExists(identifier, scope)) {
addSymbol(identifier, scope, value, type);
}
}
}
void displaySymbolTable() {
if (!symbolCount) return;
printf("\nSymbol Table:\n");
printf("Identifier\tScope\tValue\tType\n");
printf("--------------------------------------------------\n");
for (int i = 0; i < symbolCount; i++) {
printf("%s\t\t%s\t%s\t%s\n", symbolTable[i].identifier, symbolTable[i].scope, symbolTable[i].value,
symbolTable[i].type);
}
}
int main() {
char input[200], scope[10] = "global", choice[10];
while (1) {
printf("\nDo you want to (add/check/exit)? ");
scanf("%s", choice);
if (strcmp(choice, "add") == 0) {
printf("Enter the code: ");
getchar();
fgets(input, sizeof(input), stdin);
input[strcspn(input, "\n")] = '\0';
for (int i = 0; input[i]; i++) {
if (input[i] == '{') strcpy(scope, "local");
else if (input[i] == '}') strcpy(scope, "global");
else if (isalpha(input[i]) || input[i] == '_') IdentifierCheck(input + i, scope);
}
} else if (strcmp(choice, "check") == 0) {
displaySymbolTable();
} else if (strcmp(choice, "exit") == 0) {
break;
} else {
printf("Invalid choice. Please enter 'add', 'check', or 'exit'.\n");
}
}
return 0;
}