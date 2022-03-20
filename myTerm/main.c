#include <stdio.h>
#include "src/myTerm.h"

int main(){
	int rows, cols;
	mt_getscreensize(&rows, &cols);
	
	
	mt_clrscr();
	
	mt_gotoXY(8, 6);
	mt_setfgcolor(Green);
	mt_setbgcolor(White);
	printf("IP-015\n");
	mt_gotoXY(10, 5);
	mt_setfgcolor(Red);
	mt_setbgcolor(Black);
	printf("Vadim Maltsev, Matinina Ulyana\n");
	mt_gotoXY(1, 10);
	
	return 0;
}
