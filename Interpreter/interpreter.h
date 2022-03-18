#ifndef INTERPRETER_H
#define INTERPRETER_H

FILE * program;

INTERPRETER command(char code[]) {
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
    for(int i = 0; code[i] != '\0'; i++) if(code[i] == '!') return; // If comment is found, the line will end.
}
INTERPRETER readProgram(char file[]) {
    program = fopen(file, "r");
    char fileCode[500];
	while(!feof(program)) {
		fgets(fileCode, 500, program);
		if(command(fileCode) > 0) SyntaxError(READ);
	}
    fclose(program);
}
INTERPRETER endProgram() {
    getch();
    exit(0);
}
INTERPRETER SyntaxError(int error) {
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
#endif