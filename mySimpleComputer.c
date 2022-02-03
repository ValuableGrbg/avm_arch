#include "mySimpleComputer.h"

int memory[100] = {0};
int accumulator;
int instructionCounter;
int operation;
int flags[5] = {0};
int cell;
int keys;


int sc_memoryInit ()
{
	for (int i = 0; i < 100; i++){
		memory[i] = 0;
	}
}
int sc_memorySet (int address, int value)
{
	if (address < 0 || address >= 100){
		flags[OUT_OF_MEMORY_BORDERS] = 1;
		return 1;
	}
	memory[address] = value;
}

int sc_memoryGet (int address, int * value)
{
	if (address < 0 || address >= 100){
		flags[OUT_OF_MEMORY_BORDERS] = 1;
		return 1;
	}
	*value = memory[address];
}

int sc_memorySave (char * filename)
{
	FILE *output = NULL;
	output = fopen(filename, "wb");
	fwrite(memory, sizeof(int), 100, output);
	fclose(output)
}
int sc_memoryLoad (char * filename);
int sc_regInit ();
int sc_regSet (int reg, int value);
int sc_regGet (int register, int * value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);


