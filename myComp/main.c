#include "stdio.h"
#include "src/mySimpleComputer.h"

void print_mem()
{
	int val;
	printf("###########################\n");
	for (int i = 1; i < 101; i++){
		sc_memoryGet(i-1, &val);
		printf("%d ", val);
		if (i % 10 == 0){
			printf("\n");
		}
	}
	printf("###########################\n");
}

void print_bin(int num){
	int i, mask = 0x4000;//маска соответствует 14 разряду.
	printf("  Command Operand\n");
	for(i = 14; i >= 0; i--){		
		if ((num & mask) == mask)
			printf("1");
		else
			printf("0");
		if ((i == 14) || (i == 7) )
			printf(" ");
		mask /= 2;//уменьшение разряда при каждой итерации
	}	
	printf("\n");
}

void print_flags()
{
	int value;
	printf("ZERO_DIVISION: %d\n", sc_regGet(0, &value));
	printf("OVERFLOW: %d\n", sc_regGet(1, &value));
	printf("OUT_OF_MEMORY_BORDERS: %d\n", sc_regGet(2, &value));
	printf("IGNORE_TICKS: %d\n", sc_regGet(3, &value));
	printf("WRONG_COMMAND: %d\n", sc_regGet(4, &value));
}

int main()
{
	char file[] = "memory.txt";
	sc_memoryInit();
	sc_regInit();
	print_flags();
	printf("\nIt's alive!!\n");
	int value;
	for (int i = 0; i < 100; i++){
		sc_memorySet(i, i+1);
	}
	print_mem();
	sc_memorySet(102, 3);
	print_flags();
	printf("\n");
	
	sc_memorySave(file);
	sc_memoryInit();
	sc_memoryLoad(file);
	print_mem(); 
	
	int command = 0, operand = 0;
	sc_commandEncode(0x11, 0x23, &value);
	printf("\nValue (Encode_command) : %d\n\n", value);
	sc_commandDecode(value, &command, &operand);
	printf("\nCommand = 0x%X\nOperand = 0x%X\n\n", command, operand);
	print_flags();
	printf("\n\nBinary print:\n");
	print_bin(value);
	
	return 0;
}
