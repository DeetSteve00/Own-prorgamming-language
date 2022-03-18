// Special symbols
    #define STRING '"'
    #define LINEBREAK '\n' // '\n'
    #define SPACE 32 // ' '
// PROGRAM
    #define INTERPRETER void
    #define SYNTAX_FUNCTION void
    INTERPRETER varList[300]; // Max vars = 300
//

#include "interpreter.h"

/* Interpreter function declarations:
    INTERPRETER SyntaxError(int error);
    INTERPRETER endProgram();
    INTERPRETER readProgram(char file[]);
    INTERPRETER command(char code[]);
*/

SYNTAX_FUNCTION printOut(char line[]) {
    int i = 0;
    char out[300];
    for(i = 0; line[i + 5] != STRING; i++) {
        out[i] = line[i + 5];
    }
    out[i] = '\0';
    if(line[4] != STRING) {
		char varLocation[3];
        for(int i = 4; line[i] != '\0'; i++) {
            if(line[i] == (STRING || LINEBREAK)) SyntaxError(OUT);
            varLocation[i - 4] = line[i];
        }
        int varLoc = atoi(varLocation);
        printf("%d", varList[varLoc]);
    } else printf("%s", out);
}
SYNTAX_FUNCTION inputVar(char line[]) {
    char varLocation[3];
    for(int i = 4; line[i] != '\0'; i++) {
        if(line[i] == (STRING || LINEBREAK)) SyntaxError(OUT);
        varLocation[i - 4] = line[i];
    }
    int varLoc = atoi(varLocation);
    char input[1000];
    gets(input);
    varList[varLoc] = atoi(input);
}
SYNTAX_FUNCTION defineVar(char line[]) {
    int varLength = 0;
    char input[3];
    for(int i = 4; line[i] != SPACE; i++) {
        if(line[i] == (STRING || LINEBREAK)) SyntaxError(VAR);
        input[i - 4] = line[i];
        varLength++;
    }
    int varLocation = atoi(input);
    for(int i = 5 + varLength; line[i] != '\0'; i++) {
        if(line[i] == (STRING ||LINEBREAK)) SyntaxError(VAR);
        input[i - 5 - varLength] = line[i];
    }
    int varValue = atoi(input);
    varList[varLocation] = varValue;
}

// MAIN
int main(int argc, char* argv[]) {
    if(argc < 1) return 1;
    readProgram(argv[1]);
    getch();
    return 0;
}
