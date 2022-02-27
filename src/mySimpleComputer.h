#pragma once

#define ZERO_DIVISION 0
#define OVERFLOW 1
#define OUT_OF_MEMORY_BORDERS 2
#define IGNORE_TICKS 3
#define WRONG_COMMAND 4

int memory[100];
int accumulator;
int instructionCounter;
int operation;
int flags[5];
int cell;
int keys;

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int * value);
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regInit ();
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int * value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);


