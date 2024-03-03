//This module manages the parsing of the .vm input file.

#ifndef INCLUDED_ENUMS
#include "enumTypes.h"
#define INCLUDED_ENUMS
#endif

char* removeFileExtension(char*);
//Returns the file name given as parameter without the extension.

void openInputFile(char*);
//Opens the input file whose name is given as parameter.

void closeInputFile();
//Closes the input file previously opened by openInputFile(); 

int hasMoreCommands();
//Returns 1 if the opened input file has more lines; 0 otherwise.

void advance();
//Reads the next line of the opened input file.

opType getCommandType();
//Returns the type of the last command that has been read.

memAccessType getMemAccessType();
//Precondition: the last-read command is of memory-access type.
//Postcondition: the actual command (push or pop) is returned.

segmentType getSegmentType();
//Precondition: the last-read command is of memory-access type.
//Postcondition: the segment used by the command is returned.

char* getIndex();
//Precondition: the last-read command is of memory-access type.
//Postconditon: the index/constant used by the command is returned.

computeType getComputeType();
//Precondition: the last-read command is of arithmetic/boolean type.
//Postcondition: the actual command (add, sub, ...) is returned.

flowType getFlowType();
//Precondition: the last-read command is of program-flow type.
//Postcondition: the actual command (label, ...) is returned.

char* getLabel();
//Precondition: the last-read command is of program-flow type.
//Postcondition: the label used by the command is returned.

functionType getFunctionType();
//Precondition: the last-read command is of function-calling type.
//Postcondition: the actual command (call, ...) is returned.

char* getFunctionName();
//Precondition: the last-read command is of function-calling type.
//Postcondition: the name of the function used in the command is returned.

char* getFunctionParameter();
//Precondition: the last-read command is of function-calling type.
//Postcondition: the parameter used in the command is returned.

int stringToInt(char*);
//Converts the given string into an integer value.