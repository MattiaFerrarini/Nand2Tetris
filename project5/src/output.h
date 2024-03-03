//This module manages the output process, i.e. the writing of 
//the converted instruction in the .hack file

void openOutputFile(char*);
//Precondition: the argument is a string in the format NAME.asm.
//Postcondition: a file named NAME.hack is opened (if existing) or created in writing mode.

void closeOutputFile();
//Closes the output file opened by openOutputFile().

void printInstruction(char*);
//The string pointed by the parameter is written in the output file opened by openOutputFile().