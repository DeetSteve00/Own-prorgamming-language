#ifndef INTERPRETER_H
#define INTERPRETER_H

SYNTAX_FUNCTION(void) changeVar(char line[]) {
	char targetVar[3];
	int targetLength = 0;
	char compleVar[3];
	for(int i = 0; line[i + 5] != SPACE; i++) {
		if(line[i + 5] == (STRING || LINEBREAK)) SyntaxError(SET);
		targetVar[i] = line[i + 5];
		targetLength++;
	}
	targetLength += 6;
	int targetLoc = atoi(targetVar);
	for(int i = 0; line[targetLength + i] != '\0'; i++) {
		if(line[i + targetLength] == (STRING || LINEBREAK)) SyntaxError(SET);
		compleVar[i] = line[i + targetLength];
	}
	int compleLoc = atoi(compleVar);
	switch(line[3]) {
		case '+':
			varList[targetLoc] += varList[compleLoc];
			break;
		case '-':
			varList[targetLoc] -= varList[compleLoc];
			break;
		default:
			SyntaxError(SET);
			break;
	}
}
SYNTAX_FUNCTION(void) printOut(char line[]) {
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
SYNTAX_FUNCTION(void) inputVar(char line[]) {
    char varLocation[3];
    for(int i = 3; line[i] != '\0'; i++) {
        if(line[i] == (STRING || LINEBREAK)) SyntaxError(INP);
        varLocation[i - 3] = line[i];
    }
    int varLoc = atoi(varLocation);
    char input[1000];
    gets(input);
    varList[varLoc] = atoi(input);
}
SYNTAX_FUNCTION(void) defineVar(char line[]) {
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

#endif
