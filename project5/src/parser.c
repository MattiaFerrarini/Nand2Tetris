#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

FILE* fin;

char command[256];
char symbol[64];
char dest[4];
char comp[8];
char jump[4];

int commandStartIndex = 0;

void openInputFile(char* fileName){
    fin = fopen(fileName, "r");
    if(fin == NULL){
        printf("Error opening output file: %s\n", fileName);
        exit(1);
    }
}

void rewindInputFile(){
    rewind(fin);
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
    while(command[commandStartIndex] == ' ' || command[commandStartIndex] == '\t' && commandStartIndex < 256)
        commandStartIndex += 1;
}

char getCommandType(){
    commandStartIndex = 0;
    skipBlanks();

    char commandType;
    switch(command[commandStartIndex]){
        case '@': commandType = 'A'; break;
        case '(': commandType = 'L'; break;
        case 'A': case 'M': case 'D': case '0': case '1': case '-': case '!': commandType = 'C'; break;
        default: commandType = 'I'; break;
    }
    return commandType;
}

int isSymbol(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_' || c == '.' || c == '$'));
}

char* getSymbol(){
    int index = 0;
    while(isSymbol(command[commandStartIndex + 1 + index]) && index < 63){
        symbol[index] = command[commandStartIndex + 1 + index];
        index += 1;
    }
    symbol[index] = '\0';
    return(&symbol[0]);
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

char* getDest(){
    int index = 0;

    if(isIn(command, '=', commandStartIndex)){
        for(index; index < 4; index++){
            char c = command[commandStartIndex + index];
            if(c == 'A' || c == 'M' || c == 'D')
                dest[index] = c;
            else
                break;
        }
    }
    commandStartIndex += index;

    dest[index] = '\0';
    return(&dest[0]);
}

char* getComp(){
    char compCharacters[11] = {'0', '1', '+', '-', '!', '&', '|', 'A', 'D', 'M', '\0'};

    while(!isIn(compCharacters, command[commandStartIndex], 0))
        commandStartIndex += 1;
    
    int index = 0;
    while(isIn(compCharacters, command[commandStartIndex + index], 0)){
        comp[index] = command[commandStartIndex + index];
        index += 1;
    }

    commandStartIndex += index;
    comp[index] = '\0';
    return(&comp[0]);
}

char* getJump(){
    jump[0] = '\0';
    if(isIn(command, ';', commandStartIndex)){
        while(command[commandStartIndex] == ' ' || command[commandStartIndex] == ';')
            commandStartIndex += 1;
        
        for(int i = 0; i < 3; i++)
            jump[i] = command[commandStartIndex + i];
        jump[3] = '\0';
    }
    return(&jump[0]);
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