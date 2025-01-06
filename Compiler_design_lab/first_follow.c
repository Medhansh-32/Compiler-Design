#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 10
// Define grammar and variables
char productions[MAX][MAX];
char nonTerminals[MAX], terminals[MAX];
int productionCount = 0, nonTerminalCount = 0, terminalCount = 0;
char first[MAX][MAX], follow[MAX][MAX];
int firstComputed[MAX], followComputed[MAX];
// Function to find index of a symbol
int findIndex(char symbol, char *array, int count) {
for (int i = 0; i < count; i++) {
if (array[i] == symbol)
return i;
}
return -1;
}
// Add a symbol to a set (avoid duplicates)
void addToSet(char *set, char symbol) {
if (strchr(set, symbol) == NULL) {
int len = strlen(set);
set[len] = symbol;
set[len + 1] = '\0';
}
}
// Compute First set for a given non-terminal
void computeFirst(char nonTerminal) {
int index = findIndex(nonTerminal, nonTerminals, nonTerminalCount);
if (firstComputed[index]) return;
firstComputed[index] = 1;
for (int i = 0; i < productionCount; i++) {
if (productions[i][0] == nonTerminal) {
for (int j = 3; productions[i][j] != '\0'; j++) {
char symbol = productions[i][j];
if (isupper(symbol)) {
computeFirst(symbol);
int symbolIndex = findIndex(symbol, nonTerminals, nonTerminalCount);
for (int k = 0; first[symbolIndex][k] != '\0'; k++) {
if (first[symbolIndex][k] != 'ε')
addToSet(first[index], first[symbolIndex][k]);
}
if (strchr(first[symbolIndex], 'ε') == NULL) break;
} else {
addToSet(first[index], symbol);
break;
}
}
}
}
}
// Compute Follow set for a given non-terminal
void computeFollow(char nonTerminal) {
int index = findIndex(nonTerminal, nonTerminals, nonTerminalCount);
if (followComputed[index]) return;
followComputed[index] = 1;
if (nonTerminal == nonTerminals[0])
addToSet(follow[index], '$'); // Add $ to the start symbol
for (int i = 0; i < productionCount; i++) {
for (int j = 3; productions[i][j] != '\0'; j++) {
if (productions[i][j] == nonTerminal) {
int k = j + 1;
while (productions[i][k] != '\0') {
char symbol = productions[i][k];
if (isupper(symbol)) {
int symbolIndex = findIndex(symbol, nonTerminals, nonTerminalCount);
for (int l = 0; first[symbolIndex][l] != '\0'; l++) {
if (first[symbolIndex][l] != 'ε')
addToSet(follow[index], first[symbolIndex][l]);
}
if (strchr(first[symbolIndex], 'ε') == NULL)
break;
} else {
addToSet(follow[index], symbol);
break;
}
k++;
}
if (productions[i][k] == '\0' && productions[i][0] != nonTerminal) {
computeFollow(productions[i][0]);
int lhsIndex = findIndex(productions[i][0], nonTerminals, nonTerminalCount);
for (int l = 0; follow[lhsIndex][l] != '\0'; l++) {
addToSet(follow[index], follow[lhsIndex][l]);
}
}
}
}
}
}
int main() {
printf("Enter the number of productions: ");
scanf("%d", &productionCount);
printf("Enter the productions (e.g., E->T|+T):\n");
for (int i = 0; i < productionCount; i++) {
scanf("%s", productions[i]);
char nonTerminal = productions[i][0];
if (findIndex(nonTerminal, nonTerminals, nonTerminalCount) == -1) {
nonTerminals[nonTerminalCount++] = nonTerminal;
}
}
// Identify terminals
for (int i = 0; i < productionCount; i++) {
for (int j = 3; productions[i][j] != '\0'; j++) {
char symbol = productions[i][j];
if (!isupper(symbol) && symbol != '|' && symbol != 'ε') {
if (findIndex(symbol, terminals, terminalCount) == -1) {
terminals[terminalCount++] = symbol;
}
}
}
}
// Compute First and Follow sets
memset(firstComputed, 0, sizeof(firstComputed));
memset(followComputed, 0, sizeof(followComputed));
for (int i = 0; i < nonTerminalCount; i++) {
computeFirst(nonTerminals[i]);
}
for (int i = 0; i < nonTerminalCount; i++) {
computeFollow(nonTerminals[i]);
}
// Display First sets
printf("\nFirst Sets:\n");
for (int i = 0; i < nonTerminalCount; i++) {
printf("First(%c) = { ", nonTerminals[i]);
for (int j = 0; first[i][j] != '\0'; j++) {
printf("%c ", first[i][j]);
}
printf("}\n");
}
// Display Follow sets
printf("\nFollow Sets:\n");
for (int i = 0; i < nonTerminalCount; i++) {
printf("Follow(%c) = { ", nonTerminals[i]);
for (int j = 0; follow[i][j] != '\0'; j++) {
printf("%c ", follow[i][j]);
}
printf("}\n");
}
return 0;
}