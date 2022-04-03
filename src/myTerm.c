#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "myTerm.h"

int mt_clrscr() {
   int tty;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   else {
      write(tty, CLR_SCR, strlen(CLR_SCR));
      close(tty);
      return 0;
   }
}

int mt_getscreensize(int *rows, int *cols) {
   struct winsize ws;
   if (!ioctl(1, TIOCGWINSZ, &ws)) {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
      return 0;
   }
   else {
      printf("Ошибка получения размера экрана\n");
      return -1;
   }
}


int mt_gotoXY(int x, int y) {
   int tty, tty_rows, tty_cols;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   mt_getscreensize(&tty_rows, &tty_cols);
   if ((x >= 0) && (x <= tty_rows) && (y >= 0) && (y <= tty_cols)) {
      char buf[8];
      sprintf(buf, GOTO_XY, x, y);
      write(tty, buf, strlen(buf));
      close(tty);
      return 0;
   }
   else {
      printf("Неверное значение номера строки или столбца\n");
      close(tty);
      return -1;
   }
}

int mt_setfgcolor(enum colors fg) {
   int tty;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   else {
      char buf[8];
      sprintf(buf, SET_FG_COLOR, fg);
      write(tty, buf, strlen(buf));
      close(tty);
      return 0;
   }
}

int mt_setbgcolor(enum colors bg) {
   int tty;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   else {
      char buf[8];
      sprintf(buf, SET_BG_COLOR, bg);
      write(tty, buf, strlen(buf));
      close(tty);
      return 0;
   }
}
