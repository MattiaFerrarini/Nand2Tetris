#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "output.h"

char outputFileName[64];
FILE* fout;

void setOutputFileName(char* inputFileName){
    strcpy(outputFileName, inputFileName);
    strcat(outputFileName, ".asm");
}

void openOutputFile(char* inputFileName){
    setOutputFileName(inputFileName);
    fout = fopen(outputFileName, "w");

    if(fout == NULL){
        printf("Error opening output file: %s\n", outputFileName);
        exit(1);
    }
}

void closeOutputFile(){
    fclose(fout);
}

void printInstruction(char* instruction){
    fprintf(fout, "%s\n", instruction);
}