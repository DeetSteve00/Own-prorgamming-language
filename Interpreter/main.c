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
    #define COMPILER_FUNCTION(X) X
    #define SYNTAX_FUNCTION(X) X
    #define SYNTAX_ERROR 1
    #define NOERROR 0
    int varList[300]; // Max vars = 300
// FUNCTION MACROS
    #define OUT 1
    #define VAR 2
    #define INP 3
    #define READ 4
	#define SET 5
    #define NO_FUNCTION 6
// Compiler declarations
    COMPILER_FUNCTION(int) SyntaxError(int error);
    COMPILER_FUNCTION(int) endProgram();
// ------------------------------------

#include "interpreter.h"

COMPILER_FUNCTION(char*) removeComment(char string[]) { // Remove the comments from the code processing
	if(string[0] == '!') return "\n";
	char* token = strtok(string, "!");
	return token;
}
COMPILER_FUNCTION(int) command(char code[]) {
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
    } else if(strcmp(keyWord, "SET") == 0) {
		changeVar(code);
	} else if(code[0] == LINEBREAK) {
		return NOERROR;
	} else {
		SyntaxError(NO_FUNCTION);
	}
    return NOERROR;
}
COMPILER_FUNCTION(void) readProgram(char file[]) {
    program = fopen(file, "r");
    char fileCode[500];
	while(!feof(program)) {
		fgets(fileCode, 500, program);
		if(command(removeComment(fileCode)) > 0) SyntaxError(READ);
	}
    fclose(program);
}
int main(int argc, char* argv[]) {
    if(argc < 2) argv[1] = "con";
    readProgram(argv[1]);
    getch();
    return 0;
}
// ------------------------------------
COMPILER_FUNCTION(int) endProgram() {
    getch();
    exit(0);
}
COMPILER_FUNCTION(int) SyntaxError(int error) {
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
            printf("Something went wrong\n");
            break;
		case SET:
			printf("Wrong SET usage.\n");
			break;
        case NO_FUNCTION:
            printf("Unknown function");
            break;
    }
    endProgram();
}
