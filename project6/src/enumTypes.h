//This module declares various enums that will be used by the other modules
//in order to identify the type of command that has to be translated. 

enum opT {COMPUTE, MEM_ACCESS, FLOW, FUNCTION, IGNORE};
typedef enum opT opType;

enum segT {CONSTANT, STATIC, LOCAL, ARG};
typedef enum segT segmentType;

enum memAccT {PUSH, POP};
typedef enum memAccT memAccessType;

enum compT {ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT};
typedef enum compT computeType;

enum flowT {LABEL, GOTO, IF_GOTO};
typedef enum flowT flowType;

enum funcT {DECLARATION, CALL, RETURN};
typedef enum funcT functionType;