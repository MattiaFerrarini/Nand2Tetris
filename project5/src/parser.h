//This module manages the parsing of the .asm input file.

void openInputFile(char*);
//Precondition: the argument is a string in the format NAME.asm.
//Postcondition: the file is opened in reading mode.

void rewindInputFile();
//The pointer to the input file is set to the beginning of the file.

void closeInputFile();
//Closes the input file opened by openInputFile().

int hasMoreCommands();
//Returns 1 if the input file contains more lines; 0 otherwise.

void advance();
//Reads the next line of the input file.

char getCommandType();
//Returns a char corresponding to the instruction type of the last-read line:
//'A' : A instruction 
//'C' : C instruction
//'L' : Label declaration
//'I' : the line has to be Ignored

char* getSymbol();
//Precondition: the last-read instruction is an A instruction.
//Postcondition: extracts the symbol (address / variable name) from the instruction and returns it. 

char* getDest();
//Precondition: the last-read instruction is a C instruction.
//Postcondition: extracts the dest part from the instruction and returns it. 

char* getComp();
//Precondition: the last-read instruction is a C instruction.
//Postcondition: extracts the comp part from the instruction and returns it. 

char* getJump();
//Precondition: the last-read instruction is a C instruction.
//Postcondition: extracts the jump part from the instruction and returns it. 

int stringToInt(char*);
//converts a string representation of a natural number into the equivalent integer.