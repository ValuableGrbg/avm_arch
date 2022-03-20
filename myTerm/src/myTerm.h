#pragma once

#define CLR_SCR "\E[H\E[J" // Esc-последовательность очистки экрана
#define GOTO_XY "\E[%d;%dH" // Esc-последовательность перемещения курсора
#define SET_FG_COLOR "\E[3%dm" // Esc-последовательность выбора цвета текста
#define SET_BG_COLOR "\E[4%dm" // Esc-последовательность выбора фона текста

enum colors { Black = 0, Red = 1, Green = 2, Yellow = 3,
	      Blue = 4, Purple = 5, Aqua = 6, White = 7 };

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

//\E[H\E[2J -clr

