//This module manages the output process, i.e. the writing of 
//the converted instruction in the .asm file

void openOutputFile(char*);
//Precondition: the argument is a file name without extension.
//Postcondition: a file .asm with the given name is opened (if existing) or created in writing mode.

void closeOutputFile();
//Closes the output file opened by openOutputFile().

void printInstruction(char*);
//The string passed as parameter is printed on the ouput file opened by openOutputFile().