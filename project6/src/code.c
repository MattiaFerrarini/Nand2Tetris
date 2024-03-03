#include <string.h>
#include <stdio.h>
#include "code.h"

#define PUSH_STR "@SP\nA = M\nM = D\n@SP\nM = M + 1\n" //instructions to perform push
#define POP_STR "@SP\nM = M - 1\nA = M\nD = M\n" //instructions to perform pop

char* name;
char inst[512];
char num[6];

int jumpCount = 1;

void translatePush(segmentType, char*);
//Translates a push instruction that uses the segment and index/constant given as parameters.

void translatePop(segmentType, char*);
//Translates a pop instruction that uses the segment and index given as parameters.

void translateBinaryOp(computeType);
//Translates an arithmetic/boolean binary operation (add, sub, and, or) whose type is given as parameter.

void translateCompareOp(computeType);
//Translates a compare binary operation (eq, gt, lt) whose type is given as parameter.

void translateUnaryOp(computeType);
//Translates an arithmetic/boolean unary operation (neg, not) whose type is given as parameter.

void translateFunctionDecl(char*, int);
//Translates the declaration of a function whose name and nVars are given as parameters.

void translateFunctionCall(char*, char*);
//Translates the call of a function whose name and nArgs are given as parameters.

void translateFunctionReturn();
//Translates a function return command.

void intToString(int);
//Converts the integer parameter into a string.


void setSourceFileName(char* fileName){
    name = fileName;
}

char* translateStackPointerSetting(){
    strcpy(inst, "@256\nD = A\n@0\nM = D\n");
    return inst;
}

char* translateMemoryAccess(memAccessType command, segmentType segment, char* index){
    if(command == PUSH)
        translatePush(segment, index);
    else if(command == POP)
        translatePop(segment, index);
    return inst;
}

void translatePush(segmentType segment, char* index){
    if(segment == CONSTANT){
        strcpy(inst, "@"); strcat(inst, index); strcat(inst, "\nD = A\n");
    }
    else if(segment == STATIC){
        strcpy(inst, "@"); strcat(inst, name); strcat(inst, "."); strcat(inst, index); strcat(inst, "\nD = M\n");
    }
    else if(segment == LOCAL){
        strcpy(inst, "@LCL\nD = M\n@"); strcat(inst, index); strcat(inst, "\nA = D + A\nD = M\n");
    }
    else if(segment == ARG){
        strcpy(inst, "@ARG\nD = M\n@"); strcat(inst, index); strcat(inst, "\nA = D + A\nD = M\n");
    }
    strcat(inst, PUSH_STR);
}

void translatePop(segmentType segment, char* index){
    if(segment == STATIC){
        strcpy(inst, "@"); strcat(inst, name); strcat(inst, "."); strcat(inst, index); strcat(inst, "\nD = A\n");
    }
    else if(segment == LOCAL){
        strcpy(inst, "@LCL\nD = M\n@"); strcat(inst, index); strcat(inst, "\nD = D + A\n");
    }
    else if(segment == ARG){
        strcpy(inst, "@ARG\nD = M\n@"); strcat(inst, index); strcat(inst, "\nD = D + A\n");
    }
    strcat(inst, "@13\nM = D\n");
    strcat(inst, POP_STR);
    strcat(inst, "@13\nA = M\nM = D\n");
}

char* translateCompute(computeType compType){
    if(compType == NOT || compType == NEG)
        translateUnaryOp(compType);
    else if(compType == EQ || compType == GT || compType == LT)
        translateCompareOp(compType);
    else
        translateBinaryOp(compType);
    return inst;
}

void translateBinaryOp(computeType compType){
    strcpy(inst, POP_STR); 
    strcat(inst, "@13\nM = D\n");
    strcat(inst, POP_STR);
    strcat(inst, "@13\n");

    if(compType == ADD) strcat(inst, "D = D + M\n");
    else if(compType == SUB) strcat(inst, "D = D - M\n");
    else if(compType == AND) strcat(inst, "D = D & M\n");
    else if(compType == OR) strcat(inst, "D = D | M\n");

    strcat(inst, PUSH_STR);
}
void translateCompareOp(computeType compType){
    strcpy(inst, POP_STR); 
    strcat(inst, "@13\nM = D\n");
    strcat(inst, POP_STR);
    strcat(inst, "@13\nD = D - M\n@FALSE.");
    strcat(inst, name); strcat(inst, ".");

    intToString(jumpCount);
    strcat(inst, num);

    if(compType == EQ) strcat(inst, "\nD; JNE\n");
    else if(compType == GT) strcat(inst, "\nD; JLE\n");
    else if(compType == LT) strcat(inst, "\nD; JGE\n");

    strcat(inst, "D = -1\n@END."); strcat(inst, name); strcat(inst, "."); strcat(inst, num);
    strcat(inst, "\n0; JMP\n(FALSE."); strcat(inst, name); strcat(inst, ".");strcat(inst, num);
    strcat(inst, ")\nD = 0\n(END."); strcat(inst, name); strcat(inst, "."); strcat(inst, num); strcat(inst, ")\n");

    strcat(inst, PUSH_STR);
    jumpCount += 1;
}

void translateUnaryOp(computeType compType){
    strcpy(inst, POP_STR);

    if(compType == NOT) strcat(inst, "D = !D\n");
    else if(compType == NEG) strcat(inst, "D = -D\n");

    strcat(inst, PUSH_STR);
}

char* translateFlow(flowType command, char* label){
    if(command == LABEL){
        strcpy(inst, "("); strcat(inst, label); strcat(inst, ")\n");
    }
    else if(command == GOTO){
        strcpy(inst, "@"); strcat(inst, label); strcat(inst, "\n0; JMP\n");
    }
    else if(command == IF_GOTO){
        strcpy(inst, POP_STR); strcat(inst, "@"); strcat(inst, label); strcat(inst, "\nD; JNE\n");
    }
    return inst;
}

char* translateFunction(functionType command, char* functionName, char* parameterStr, int parameterInt){
    if(command == DECLARATION) 
        translateFunctionDecl(functionName, parameterInt);
    else if(command == CALL)
        translateFunctionCall(functionName, parameterStr);
    else if(command == RETURN)
        translateFunctionReturn();
    return inst;
}

void translateFunctionDecl(char* functionName, int parameter){
    strcpy(inst, "("); strcat(inst, name); strcat(inst, ".");
    strcat(inst, functionName); strcat(inst, ")\n");
    for(int i = 0; i < parameter; i++)
        strcat(inst, "@SP\nA = M\nM = 0\n@SP\nM = M + 1\n");
}
void translateFunctionCall(char* functionName, char* parameter){
    //Push return-address
    strcpy(inst, "@"); strcat(inst, functionName);
    strcat(inst, "$ret."); intToString(jumpCount); strcat(inst, num); 
    strcat(inst, "\nD = A\n"); strcat(inst, PUSH_STR);

    //Push LCL, ARG, THIS, THAT
    strcat(inst, "@LCL\nD = M\n"); strcat(inst, PUSH_STR);
    strcat(inst, "@ARG\nD = M\n"); strcat(inst, PUSH_STR);
    strcat(inst, "@THIS\nD = M\n"); strcat(inst, PUSH_STR);
    strcat(inst, "@THAT\nD = M\n"); strcat(inst, PUSH_STR);

    //Reposition ARG
    strcat(inst, "@SP\nD = M\n@5\nD = D - A\n@"); strcat(inst, parameter); 
    strcat(inst, "\nD = D - A\n@ARG\nM = D\n");

    //Reposition LCL
    strcat(inst, "@SP\nD = M\n@LCL\nM = D\n");

    //Goto function
    strcat(inst, "@"); strcat(inst, name); strcat(inst, "."); strcat(inst, functionName);
    strcat(inst, "\n0; JMP\n");
    
    //Declare return-address label
    strcat(inst, "("); strcat(inst, functionName);
    strcat(inst, "$ret."); strcat(inst, num); strcat(inst, ")\n");

    jumpCount += 1;
}
void translateFunctionReturn(){
    strcpy(inst, "@LCL\nD = M\n@13\nM = D\n"); //FRAME = LCL 
    strcat(inst, "@5\nD = D - A\nA = D\nD = M\n@14\nM = D\n"); //RET = *(FRAME - 5)
    strcat(inst, POP_STR); strcat(inst, "@ARG\nA = M\nM = D\n"); //*ARG = pop()
    strcat(inst, "@ARG\nD = M\nD = D + 1\n@SP\nM = D\n"); //SP = ARG + 1
    strcat(inst, "@13\nM = M - 1\nA = M\nD = M\n@THAT\nM = D\n"); //THAT = *(FRAME - 1)
    strcat(inst, "@13\nM = M - 1\nA = M\nD = M\n@THIS\nM = D\n"); //THIS = *(FRAME - 2)
    strcat(inst, "@13\nM = M - 1\nA = M\nD = M\n@ARG\nM = D\n"); //ARG = *(FRAME - 3)
    strcat(inst, "@13\nM = M - 1\nA = M\nD = M\n@LCL\nM = D\n"); //LCL = *(FRAME - 4)
    strcat(inst, "@14\nA = M\n0; JMP\n");//goto RET
}

void intToString(int val){
    int index = 0;
    while(val > 0 && index < 5){
        num[index] = (char)(48 + val % 10);
        val = val / 10;
        index += 1;
    }
    num[index] = '\0';
}