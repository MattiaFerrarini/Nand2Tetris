//This module manages the convertion of hack assembly expressions into the 
//corresponding binary codes.

char* intToBinary(int);
//Precondition: the argument is a natural number <= 32767.
//Postcondition: returns a string containing the 15-bit binary equivalent of the given number.

char* translateComp(char*);
//Precondition: the argument is a string containing a comp mnemonic.
//Postcondition: returns a string containing the binary code corrsponding to the given mnemonic.

char* translateDest(char*);
//Precondition: the argument is a string containing a dest mnemonic.
//Postcondition: returns a string containing the binary code corrsponding to the given mnemonic.

char* translateJump(char*);
//Precondition: the argument is a string containing a jump mnemonic.
//Postcondition: returns a string containing the binary code corrsponding to the given mnemonic.