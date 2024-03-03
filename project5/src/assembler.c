#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"
#include "output.h"

void createSymbolTable();
//Creates the symbol table, including predefined symbols and custom labels, but not variables.
void findLabels();
//Goes through the file .asm, finds labels and adds them to the symbol table.

void translateFile();
//Translates the .asm file into the corresponding .hack file.
void translateCommand(char);
//Translates the last-read instruction into the corresponding binary code.
void translateAssignment();
//Translates an A-instruction into the corresponding binary code.
void translateCompute();
//Translates a C-instruction into the corresponding binary code.

int getSymbolTableAddress(char*);
//Retrieves the address associated to a label from the symbol table.

void setAssignment(char*);
//Uses the provided 15-bit binary number to set the instruction string to represent an A-instruction.
void setCompute(char*, char*, char*);
//Uses the provided comp, dest and jump strings to set the instruction string to represent a C-instruction

char instruction[17];

int main(int argc, char **argv){
    if(argc >= 2){
        openInputFile(argv[1]);
        openOutputFile(argv[1]);

        createSymbolTable();
        rewindInputFile();
        translateFile();

        closeInputFile();
        closeOutputFile();
    }
    else{
        printf("Missing one argument.\n");
        exit(1);
    }
}

void createSymbolTable(){
    initializeTable();
    findLabels();
}

void findLabels(){
    int lineNumber = 0;
    int endOfFile = 0;
    
    while(!endOfFile){
        advance();
        if(hasMoreCommands()){
            char commandType = getCommandType();
            if(commandType == 'L')
                addEntry(getSymbol(), lineNumber);
            else if(commandType != 'I')
                lineNumber += 1;
        }
        else
            endOfFile = 1;
    }
}

void translateFile(){
    int endOfFile = 0;
    while(!endOfFile){
        advance();
        if(hasMoreCommands()){
            char commandType = getCommandType();
            translateCommand(commandType);
        }
        else
            endOfFile = 1;
    }
}

void translateCommand(char commandType){
    if(commandType == 'A')
        translateAssignment();
    else if(commandType == 'C')
        translateCompute();

    if(commandType == 'A' || commandType == 'C')
        printInstruction(instruction);
}

void translateAssignment(){
    char* symbol = getSymbol();
    int address = 0;
    
    if(symbol[0] >= '0' && symbol[0] <= '9')
        address = stringToInt(symbol);
    else
        address = getSymbolTableAddress(symbol);

    char* binarySymbol = intToBinary(address);
    setAssignment(binarySymbol);
}

int getSymbolTableAddress(char* symbol){
    if(tableContains(symbol))
        return(getAddress(symbol));
    else
        return(addVariable(symbol));
}

void translateCompute(){
    char* dest = getDest();
    char* binaryDest = translateDest(dest);

    char* comp = getComp();
    char* binaryComp = translateComp(comp);

    char* jump = getJump();
    char* binaryJump = translateJump(jump);

    setCompute(binaryComp, binaryDest, binaryJump);
}

void setAssignment(char* value){
    strcpy(instruction, "0");
    strcat(instruction, value);
}

void setCompute(char* comp, char* dest, char* jump){
    strcpy(instruction, "111");
    strcat(instruction, comp);
    strcat(instruction, dest);
    strcat(instruction, jump);
}