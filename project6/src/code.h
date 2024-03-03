//This module manages the conversion of VM commands into the 
//corresponding hack assembly instructions.

#ifndef INCLUDED_ENUMS
#include "enumTypes.h"
#define INCLUDED_ENUMS
#endif

void setSourceFileName(char*);
//Saves the file name (without the extension) passed as parameter in a local variable.
//Must be called before beginning the translation process.

char* translateStackPointerSetting();
//Returns the string of assembly instructions necessary to set SP = 256.
//Should be called at the beginning of file translation in order to facilitate subsequent testing.

char* translateMemoryAccess(memAccessType, segmentType, char*);
//This function translates memory-access commands: pop, push.
//Precondition: the parameters are the type of memory access, the segment and the index/constant used.
//Postcondition: the string of assembly instructions corresponding to the command is returned.

char* translateCompute(computeType);
//This function translates arithmetic/boolean commands: add, sub, neg, eq, gt, lt, and, or, not.
//Precondition: the parameter is the type of arithmetic/boolean operation.
//Postcondition: the string of assembly instructions corresponding to the command is returned.

char* translateFlow(flowType, char*);
//This function translates program-flow commands: label, goto, if-goto.
//Precondition: the parameters are the type of the command and the label used.
//Postcondition: the string of assembly instructions corresponding to the command is returned.

char* translateFunction(functionType, char*, char*, int);
//This function translates function-calling commands: function, call, return.
//Precondition: the parameters are the command type, the function name and the parameter used (both in string and int format).
//Postcondition: the string of assembly instructions corresponding to the command is returned.