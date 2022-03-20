#include "src/mySimpleComputer.h"
#include <stddef.h>
#include <stdio.h>

int sc_regInit()
{
	sc_register = 0;
	return 0;
}

int sc_regSet (int reg, int value)
{
	if ((value  != 0) && (value != 1)){
		return -1;
	}
	if ( (reg != 0) && (reg != 1) && (reg != 2) && (reg != 3) && (reg != 4) ){
		return -1;	
	}
	
	if (value == 1) sc_register = sc_register|(1<<(reg-1));
	else if (value == 0) sc_register = sc_register&(~(1<<(reg-1)));
	return 0;
}

int sc_regGet (int reg, int * value)
{
	if ( (reg != 0) && (reg != 1) && (reg != 2) && (reg != 3) && (reg != 4) ){
		return -1;	
	}
	*value = (sc_register >> (reg-1))&0x1;
	return 0;
}

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
		sc_regSet(OUT_OF_MEMORY_BORDERS, 1);
		return -1;
	}
	memory[address] = value;
	return 0;
}

int sc_memoryGet (int address, int * value)
{
	if (address < 0 || address >= 100){
		sc_regSet(OUT_OF_MEMORY_BORDERS, 1);
		return -1;
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

int sc_commandEncode (int command, int operand, int * value)
{
	if ( (command < 0) || (command > 0x7F) ){
		sc_regSet(WRONG_COMMAND, 1);				
		return -1;
	}
	if ( (operand < 0) || (operand > 0x7F) ){
		sc_regSet(WRONG_COMMAND, 1);
		return -1;
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
		return -1;
	}
}




