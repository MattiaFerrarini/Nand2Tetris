#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

struct hashTable
{
    char* symbol;
    int address;
    struct hashTable* next;
};
typedef struct hashTable* HASH_TABLE;

HASH_TABLE table =  NULL;
int variableCount = 16;

void addEntry(char* symbol, int address){
    HASH_TABLE newLine = (HASH_TABLE) malloc(sizeof(struct hashTable));

    newLine -> address = address;

    int length = strlen(symbol) + 1;
    newLine -> symbol = (char*) malloc(sizeof(char) * length);
    strcpy(newLine -> symbol, symbol);

    newLine -> next = table;
    table = newLine;
}

int addVariable(char* variable){
    addEntry(variable, variableCount);
    variableCount += 1;
    return(variableCount - 1);
}

void initializeTable(){
    HASH_TABLE table =  NULL;
    variableCount = 16;

    addEntry("SP", 0);
    addEntry("LCL", 1);
    addEntry("ARG", 2);
    addEntry("THIS", 3);
    addEntry("THAT", 4);
    addEntry("R0", 0);
    addEntry("R1", 1);
    addEntry("R2", 2);
    addEntry("R3", 3);
    addEntry("R4", 4);
    addEntry("R5", 5);
    addEntry("R6", 6);
    addEntry("R7", 7);
    addEntry("R8", 8);
    addEntry("R9", 9);
    addEntry("R10", 10);
    addEntry("R11", 11);
    addEntry("R12", 12);
    addEntry("R13", 13);
    addEntry("R14", 14);
    addEntry("R15", 15);
    addEntry("SCREEN", 16384);
    addEntry("KBD", 24576);
}

int tableContains(char* symbol){
    int found = 0;
    HASH_TABLE currentLine = table;

    while(currentLine != NULL && !found){
        if(strcmp(symbol, currentLine -> symbol) == 0)
            found = 1;
        else
            currentLine = currentLine -> next;
    }
    return found;
}

int getAddress(char* symbol){
    int found = 0;
    HASH_TABLE currentLine = table;

    while(currentLine != NULL && !found){
        if(strcmp(currentLine -> symbol, symbol) == 0)
            found = 1;
        else
            currentLine = currentLine -> next;
    }
    return(currentLine -> address);
}