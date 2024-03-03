//This module manages the association between symbols and the associated memory addresses.

void initializeTable();
//The symbol table is initialized with the predefined symbols and their corresponding addresses.

void addEntry(char*, int);
//Precondition: the arguments are a symbol and its corresponding address.
//Postcondition: the pair symbol-address is added to the symbol table.

int addVariable(char*);
//Precondition: the argument is a variable name.
//Postcondition: the first unused address starting from 16 is associated to the variable name.
//The pair variable-address is added to the symbol table and the address is returned.

int tableContains(char*);
//Precondition: the argument is a symbol.
//Postcondition: returns 1 if the symbol table contains the symbol; 0 otherwise.

int getAddress(char*);
//Precondition: the argument is a symbol in the symbol table.
//Postcondition: the address associated to the symbol is returned.