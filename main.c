#include "stdio.h"
#include "src/mySimpleComputer.h"

int main()
{
	printf("It's alive!!\n");
	int *value;
	for (int i = 0; i < 100; i++){
		sc_memorySet(i, i+1);
	}
	sc_memoryGet(50, value);
	printf("%d\n", *value);
	return 0;
}
