#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
FILE * program;

// Special symbols
    #define STRING '"'
    #define LINEBREAK '\n' // '\n'
    #define SPACE 32 // ' '
// PROGRAM
    #define COMPILER_FUNCTION int
    #define SYNTAX_FUNCTION void
    #define SYNTAX_ERROR 1
    #define NOERROR 0
    int varList[300]; // Max vars = 300
// FUNCTION MACROS
    #define OUT 1
    #define VAR 2
    #define INP 3
    #define READ 4
    #define NO_FUNCTION 5
// Compiler declarations
    COMPILER_FUNCTION SyntaxError(int error);
    COMPILER_FUNCTION endProgram();
// ------------------------------------

#include "interpreter.h"

COMPILER_FUNCTION command(char code[]) {
    char keyWord[4] = {code[0], code[1], code[2], '\0'};
    if(strcmp(keyWord, "VAR") == 0) {
        defineVar(code);
    } else if(strcmp(keyWord, "INP") == 0) {
        inputVar(code);   
    } else if(strcmp(keyWord, "OUT") == 0) {
        printOut(code);
    } else if(strcmp(keyWord, "END") == 0) {
        endProgram();
    } else if(strcmp(keyWord, "NLN") == 0) {
        printf("\n");
    }
    for(int i = 0; code[i] != '\0'; i++) if(code[i] == '!') return NOERROR; // If comment is found, the line will end.
}
COMPILER_FUNCTION readProgram(char file[]) {
    program = fopen(file, "r");
    char fileCode[500];
	while(!feof(program)) {
		fgets(fileCode, 500, program);
		if(command(fileCode) > 0) SyntaxError(READ);
	}
    fclose(program);
}
int main(int argc, char* argv[]) {
    if(argc < 1) return 1;
    readProgram(argv[1]);
    getch();
    return 0;
}
// ------------------------------------
COMPILER_FUNCTION endProgram() {
    getch();
    exit(0);
}
COMPILER_FUNCTION SyntaxError(int error) {
    printf("ERROR: ");
    switch(error) {
        case OUT:
            printf("Wrong OUT usage.\n");
            break;
        case VAR:
            printf("Wrong VAR usage.\n");
            break;
        case INP:
            printf("Wrong INP usage.\n");
            break;
        case READ:
            printf("Something went wrong with the compiler\n");
            break;
        case NO_FUNCTION:
            printf("Unknown function");
            break;
    }
    getch();
    exit(1);
}