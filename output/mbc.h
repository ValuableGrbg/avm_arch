#pragma once
#include "myTerm.h"

enum BIGCHAR {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
    NINE, A, B, C, D, E, F, PLUS, MINUS,
};

#define ENTER_ALT_CHARSET_MODE "\E(0" // Esc-последовательность включения дополнительной таблицы кодировок
#define EXIT_ALT_CHARSET_MODE "\E(B" // Esc-последовательность выключения дополнительной таблицы кодировок
#define ACS_CHARS "'afgijklmnopqrstuvwxyz{|}~" // строка соответствия символов

int big[2]; 

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar (int [2], int x, int y, enum colors, enum colors);
int bc_setbigcharpos (int * big, int x, int y, int value);
int bc_getbigcharpos(int * big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int * big, int count);
int bc_bigcharread (int fd, int * big, int need_count, int * count);
