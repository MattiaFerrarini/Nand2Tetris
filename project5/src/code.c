#include "code.h"
#include <string.h>

char binaryDest[4];
char binaryComp[8];
char binaryJump[4];
char binarySymbol[16];

char* intToBinary(int value){
    int index = 14;
    while(index >= 0 && value > 0){
        int remainder = value % 2;

        if(remainder == 0)
            binarySymbol[index] = '0';
        else
            binarySymbol[index] = '1';

        value = value / 2;
        index -= 1;
    }
    while(index >= 0){
        binarySymbol[index] = '0';
        index -= 1;
    }

    binarySymbol[15] = '\0';
    return binarySymbol;
}

char* translateDest(char* dest){
    if(strcmp(dest, "M") == 0) strcpy(binaryDest, "001");
    else if(strcmp(dest, "D") == 0) strcpy(binaryDest, "010");
    else if(strcmp(dest, "MD") == 0) strcpy(binaryDest, "011");
    else if(strcmp(dest, "A") == 0) strcpy(binaryDest, "100");
    else if(strcmp(dest, "AM") == 0) strcpy(binaryDest, "101");
    else if(strcmp(dest, "AD") == 0) strcpy(binaryDest, "110");
    else if(strcmp(dest, "AMD") == 0) strcpy(binaryDest, "111");
    else strcpy(binaryDest, "000");

    return binaryDest;
}

char* translateJump(char* jump){
    if(strcmp(jump, "JGT") == 0) strcpy(binaryJump, "001");
    else if(strcmp(jump, "JEQ") == 0) strcpy(binaryJump, "010");
    else if(strcmp(jump, "JGE") == 0) strcpy(binaryJump, "011"); 
    else if(strcmp(jump, "JLT") == 0) strcpy(binaryJump, "100");
    else if(strcmp(jump, "JNE") == 0) strcpy(binaryJump, "101"); 
    else if(strcmp(jump, "JLE") == 0) strcpy(binaryJump, "110");
    else if(strcmp(jump, "JMP") == 0) strcpy(binaryJump, "111");
    else strcpy(binaryJump, "000");

    return binaryJump;
}

char* translateComp(char* comp){
    if(strcmp(comp, "0") == 0) strcpy(binaryComp, "0101010");
    else if(strcmp(comp, "1") == 0) strcpy(binaryComp, "0111111");
    else if(strcmp(comp, "-1") == 0) strcpy(binaryComp, "0111010");
    else if(strcmp(comp, "D") == 0) strcpy(binaryComp, "0001100");
    else if(strcmp(comp, "A") == 0) strcpy(binaryComp, "0110000");
    else if(strcmp(comp, "!D") == 0) strcpy(binaryComp, "0001101");
    else if(strcmp(comp, "!A") == 0) strcpy(binaryComp, "0110001");
    else if(strcmp(comp, "-D") == 0) strcpy(binaryComp, "0001111");
    else if(strcmp(comp, "-A") == 0) strcpy(binaryComp, "0110011");
    else if(strcmp(comp, "D+1") == 0) strcpy(binaryComp, "0011111");
    else if(strcmp(comp, "A+1") == 0) strcpy(binaryComp, "0110111");
    else if(strcmp(comp, "D-1") == 0) strcpy(binaryComp, "0001110");
    else if(strcmp(comp, "A-1") == 0) strcpy(binaryComp, "0110010");
    else if(strcmp(comp, "D+A") == 0) strcpy(binaryComp, "0000010");
    else if(strcmp(comp, "D-A") == 0) strcpy(binaryComp, "0010011");
    else if(strcmp(comp, "A-D") == 0) strcpy(binaryComp, "0000111");
    else if(strcmp(comp, "D&A") == 0) strcpy(binaryComp, "0000000");
    else if(strcmp(comp, "D|A") == 0) strcpy(binaryComp, "0010101");
    else if(strcmp(comp, "M") == 0) strcpy(binaryComp, "1110000");
    else if(strcmp(comp, "!M") == 0) strcpy(binaryComp, "1110001");
    else if(strcmp(comp, "-M") == 0) strcpy(binaryComp, "1110011");
    else if(strcmp(comp, "M+1") == 0) strcpy(binaryComp, "1110111");
    else if(strcmp(comp, "M-1") == 0) strcpy(binaryComp, "1110010");
    else if(strcmp(comp, "D+M") == 0) strcpy(binaryComp, "1000010");
    else if(strcmp(comp, "D-M") == 0) strcpy(binaryComp, "1010011");
    else if(strcmp(comp, "M-D") == 0) strcpy(binaryComp, "1000111");
    else if(strcmp(comp, "D&M") == 0) strcpy(binaryComp, "1000000");
    else if(strcmp(comp, "D|M") == 0) strcpy(binaryComp, "1010101");

    return binaryComp;
}