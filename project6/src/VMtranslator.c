#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "code.h"
#include "output.h"

char* instruction;
char* file_name;

void setStackPointer();
//Prints on the .asm file the string of instructions necessary to set SP = 256

void translateFile();
//Translates the .vm file into an .asm file

void translateCommand(opType);
//Translate a single virtual-machine command.

void memoryAccess();
//Translate a VM instruction of memory-access type.

void compute();
//Translate a VM instruction of arithmetic/boolean type.

void flow();
//Translate a VM instruction of program-flow type.

void function();
//Translate a VM instruction of function-calling type.


int main(int argc, char **argv){
    if(argc >= 2){
        file_name = removeFileExtension(argv[1]);

        openInputFile(argv[1]);
        openOutputFile(file_name);

        setSourceFileName(file_name);
        translateFile();

        closeInputFile();
        closeOutputFile();
    }
    else{
        printf("Missing one argument.\n");
        exit(1);
    }
}

void translateFile(){
    setStackPointer();

    int endOfFile = 0;
    while(!endOfFile){
        advance();

        if(hasMoreCommands()){
            opType commandType = getCommandType();

            if(commandType != IGNORE){
                translateCommand(commandType);
                printInstruction(instruction);
            }
        }
        else
            endOfFile = 1;
    }
}

void setStackPointer(){
    instruction = translateStackPointerSetting();
    printInstruction(instruction);
}

void translateCommand(opType commandType){
    if(commandType == COMPUTE) 
        compute();
    else if(commandType == MEM_ACCESS) 
        memoryAccess();
    else if(commandType == FLOW) 
        flow();
    else if(commandType == FUNCTION) 
        function();
}

void memoryAccess(){
    memAccessType command = getMemAccessType();
    segmentType segment = getSegmentType();
    char* index = getIndex();
    instruction = translateMemoryAccess(command, segment, index);
}

void compute(){
    computeType command = getComputeType();
    instruction = translateCompute(command);
}

void flow(){
    flowType command = getFlowType();
    char* label = getLabel();
    instruction = translateFlow(command, label);
}

void function(){
    functionType command = getFunctionType();
    char* functionName = NULL;
    char* parameterStr = NULL;
    int parameterInt = 0;
    
    if(command == DECLARATION || command == CALL){
        functionName = getFunctionName();
        parameterStr = getFunctionParameter();
        parameterInt = stringToInt(parameterStr);
    }
    instruction = translateFunction(command, functionName, parameterStr, parameterInt);
}