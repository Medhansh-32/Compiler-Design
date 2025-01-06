#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
// Symbol table
struct Symbol {
char label[10];
int address;
} symbolTable[MAX];
int symbolCount = 0;
// Function to add a symbol
void addSymbol(char *label, int address) {
strcpy(symbolTable[symbolCount].label, label);
symbolTable[symbolCount].address = address;
symbolCount++;
}
// Function to get symbol address
int getSymbolAddress(char *label) {
for (int i = 0; i < symbolCount; i++) {
if (strcmp(symbolTable[i].label, label) == 0) {
return symbolTable[i].address;
}
}
return -1; // Label not found
}
// Main function for the one-pass assembler
void onePassAssembler() {
FILE *input = fopen("input.asm", "r");
FILE *output = fopen("output.obj", "w");
if (!input || !output) {
printf("Error opening files.\n");
return;
}
char line[100], label[10], opcode[10], operand[10];
int locationCounter = 0;
printf("One-Pass Assembler\n");
printf("-------------------\n");
while (fgets(line, sizeof(line), input)) {
int items = sscanf(line, "%s %s %s", label, opcode, operand);
if (items == 3) { // Label, opcode, operand
addSymbol(label, locationCounter);
} else if (items == 2) { // Opcode, operand
strcpy(opcode, label);
strcpy(operand, opcode);
}
// Generate machine code
if (strcmp(opcode, "MOV") == 0) {
fprintf(output, "01 %s\n", operand);
} else if (strcmp(opcode, "ADD") == 0) {
fprintf(output, "02 %s\n", operand);
} else if (strcmp(opcode, "END") == 0) {
fprintf(output, "FF\n");
break;
}
locationCounter++;
}
fclose(input);
fclose(output);
printf("Assembling complete. Check output.obj for machine code.\n");
}

void twoPassAssembler() {
FILE *input = fopen("input.asm", "r");
FILE *output = fopen("output.obj", "w");
if (!input || !output) {
printf("Error opening files.\n");
return;
}
char line[100], label[10], opcode[10], operand[10];
int locationCounter = 0;
printf("Two-Pass Assembler\n");
printf("-------------------\n");
// First pass: Build symbol table
while (fgets(line, sizeof(line), input)) {
int items = sscanf(line, "%s %s %s", label, opcode, operand);
if (items == 3) { // Label, opcode, operand
addSymbol(label, locationCounter);
}
locationCounter++;
}
// Rewind the file for the second pass
rewind(input);
locationCounter = 0;
// Second pass: Generate machine code
while (fgets(line, sizeof(line), input)) {
int items = sscanf(line, "%s %s %s", label, opcode, operand);
if (items == 3) { // Label, opcode, operand
strcpy(opcode, opcode);
strcpy(operand, operand);
} else if (items == 2) { // Opcode, operand
strcpy(opcode, label);
strcpy(operand, opcode);
}
// Generate machine code
if (strcmp(opcode, "MOV") == 0) {
fprintf(output, "01 %d\n", getSymbolAddress(operand));
} else if (strcmp(opcode, "ADD") == 0) {
fprintf(output, "02 %d\n", getSymbolAddress(operand));
} else if (strcmp(opcode, "END") == 0) {
fprintf(output, "FF\n");
break;
}
locationCounter++;
}
fclose(input);
fclose(output);
printf("Assembling complete. Check output.obj for machine code.\n");
}
