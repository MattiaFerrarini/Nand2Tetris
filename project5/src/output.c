#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "output.h"

FILE* fout;

void openOutputFile(char* inputFileName){
    char outputFileName[64];
    strcpy(outputFileName, inputFileName);
    outputFileName[strlen(outputFileName) - 3] = '\0';
    strcat(outputFileName, "hack");

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