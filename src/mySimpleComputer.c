#include "mySimpleComputer.h"
#include <stddef.h>
#include <stdio.h>

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
	return 0;
}
int sc_memorySet (int address, int value)
{
	if (address < 0 || address >= 100){
		flags[OUT_OF_MEMORY_BORDERS] = 1;
		return 1;
	}
	memory[address] = value;
	return 0;
}

int sc_memoryGet (int address, int * value)
{
	if (address < 0 || address >= 100){
		flags[OUT_OF_MEMORY_BORDERS] = 1;
		return 1;
	}
	*value = memory[address];
	return 0;
}

int sc_memorySave (char * filename)
{
	FILE *f = NULL;
	f = fopen(filename, "wb");
	if (f == NULL) return 1;
	fwrite(memory, sizeof(int), 100, f);
	fclose(f);
	return 0;
}
int sc_memoryLoad (char * filename)
{
	FILE *f = NULL;
	f = fopen(filename, "rb");
	if (f == NULL) return 1;
	fread(memory, sizeof(int), 100, f);
	fclose(f);
}
int sc_regInit()
{
	for (int i = 0; i < 5; i++){
		flags[i] = 0;
	}
	return 0;
}
int sc_regSet (int reg, int value)
{
	if(flags[reg] >= 5 || flags[reg] < 0){
		return 1;
	}
	if(value <=0 || value >=1){
		return 1;
	}
	flags[reg] = value;
	return 0;
}
int sc_regGet (int reg, int * value)
{
	if(flags[reg] >= 5 || flags[reg] < 0){
		return 1;
	}
	flags[reg] = &value;
	return 0;
}
int sc_commandEncode (int command, int operand, int * value)
{
	if ( (command < 0) || (command > 0x7F) ){
		sc_regSet(WRONG_COMMAND, 1);				
		return 1;
	}
	if ( (operand < 0) || (operand > 0x7F) ){
		sc_regSet(WRONG_COMMAND, 1);
		return 1;
	}
	*value = command;
	*value = (*value << 7);
	*value += operand;
	return 0;	
}
int sc_commandDecode (int value, int * command, int * operand)
{
	int tempOperand, tempCommand;
	tempOperand = value & 0x7F;	
	tempCommand = (value >> 7) & 0x7F;
	if ( ((tempCommand >= 0x10) && (tempCommand <= 0x11)) || ((tempCommand >= 0x20) && (tempCommand <= 0x21)) || 
		((tempCommand >= 0x30) && (tempCommand <= 0x33)) || ((tempCommand >= 0x40) && (tempCommand <= 0x43)) || 
		((tempCommand >= 0x51) && (tempCommand <= 0x76)) ){
		*command = tempCommand;
		*operand = tempOperand;		
		return 0;	
	}
	else{	
		sc_regSet(WRONG_COMMAND, 1);
		return 1;
	}
}

int main()
{
	printf("It's alive!!\n");
	return 0;
}


