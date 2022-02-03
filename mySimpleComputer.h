#ifndef HEADER
#define HEADER

#define ZERO_DIVISION = 1
#define OVERFLOW = 2
#define OUT_OF_MEMORY_BORDERS = 3
#define IGNORE_TICKS = 4
#define WRONG_COMMAND = 5


int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int * value);
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regInit ();
int sc_regSet (int reg, int value);
int sc_regGet (int register, int * value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);

#endif
