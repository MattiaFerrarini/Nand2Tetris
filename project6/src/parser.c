#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

FILE* fin;

char fileName[64];
char command[256];
char word[64];
char parameter[20];

int commandStartIndex = 0;

char* removeFileExtension(char* fName){
    strcpy(fileName, fName);
    int index = 0;
    while(fName[index] != '.')
         index += 1;

    fileName[index] = '\0';
    return fileName;
}

void openInputFile(char* vmFile){
    fin = fopen(vmFile, "r");

    if(fin == NULL){
        printf("Error opening output file: %s\n", vmFile);
        exit(1);
    }
}

void closeInputFile(){
    fclose(fin);
}

int hasMoreCommands(){
    return(!feof(fin));
}

void advance(){
    fgets(command, 256, fin);
}

void skipBlanks(){
    while(command[commandStartIndex] == ' ' || command[commandStartIndex] == '\t')
        commandStartIndex += 1;
}

int isSymbol(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_' || c == '-' || c == '.' || c == '$'));
}

void nextWord(char* dest){
    skipBlanks();
    int index = 0;
    while(isSymbol(command[commandStartIndex + index])){
        dest[index] = command[commandStartIndex + index];
        index += 1;
    }
    dest[index] = '\0';
    commandStartIndex += index;
}

opType getCommandType(){
    commandStartIndex = 0;
    nextWord(word);

    if(word[0] < 'a' || word[0] > 'z') return IGNORE;
    else if(strcmp(word, "pop") == 0 || strcmp(word, "push") == 0) return MEM_ACCESS;
    else if(strcmp(word, "label") == 0 || strcmp(word, "goto") == 0 || strcmp(word, "if-goto") == 0) return FLOW;
    else if(strcmp(word, "function") == 0 || strcmp(word, "call") == 0 || strcmp(word, "return") == 0) return FUNCTION;
    else return COMPUTE;
}

segmentType getSegmentType(){
    nextWord(word);
    if(strcmp(word, "constant") == 0) return CONSTANT;
    else if(strcmp(word, "static") == 0) return STATIC;
    else if(strcmp(word, "local") == 0) return LOCAL;
    else if(strcmp(word, "argument") == 0) return ARG;
}

memAccessType getMemAccessType(){
    if(strcmp(word, "pop") == 0) return POP;
    else if (strcmp(word, "push") == 0) return PUSH;
}

char* getIndex(){
    nextWord(parameter);
    return parameter;
}

computeType getComputeType(){
    if(strcmp(word, "add") == 0) return ADD;
    else if(strcmp(word, "sub") == 0) return SUB;
    else if(strcmp(word, "neg") == 0) return NEG;
    else if(strcmp(word, "eq") == 0) return EQ;
    else if(strcmp(word, "gt") == 0) return GT;
    else if(strcmp(word, "lt") == 0) return LT;
    else if(strcmp(word, "and") == 0) return AND;
    else if(strcmp(word, "or") == 0) return OR;
    else if(strcmp(word, "not") == 0) return NOT;
}

flowType getFlowType(){
    if(strcmp(word, "label") == 0) return LABEL;
    else if (strcmp(word, "goto") == 0) return GOTO;
    else if(strcmp(word, "if-goto") == 0) return IF_GOTO;
}

char* getLabel(){
    nextWord(word);
    return word;
}

functionType getFunctionType(){
    if(strcmp(word, "function") == 0) return DECLARATION;
    else if (strcmp(word, "call") == 0) return CALL;
    else if(strcmp(word, "return") == 0) return RETURN;
}

char* getFunctionName(){
    nextWord(word);
    return word;
}

char* getFunctionParameter(){
    nextWord(parameter);
    return parameter;
}

int isIn(char* arr, char el, int startIndex){
    int found = 0;
    while(!found && arr[startIndex] != '\0'){
        if(arr[startIndex] == el)
            found = 1;
        else
            startIndex += 1;
    }
    return found;
}

int stringToInt(char* str){
    int value = 0;
    int index = 0, multiplier = 1;
    while(str[index] != '\0'){
        int v = (int)(str[index] - '0');
        value = value * 10;
        value += v;

        multiplier = multiplier * 10;
        index += 1;
    }
    return value;
}