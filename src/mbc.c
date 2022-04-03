#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "mbc.h"

int bc_printA (char * str)
{
	int tty;
   	tty = open("/dev/tty", O_RDWR);
   	if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   	}	
   	else {
      write(tty, ENTER_ALT_CHARSET_MODE, 3);
      write(tty, str, strlen(str));
      write(tty, EXIT_ALT_CHARSET_MODE, 3);
      close(tty);
      return 0;
   	}
}

int bc_box(int x1, int y1, int x2, int y2)
{
	int tty, i, j;
	tty = open("/dev/tty", O_RDWR);
	if (tty == -1) {
		printf("Невозможно открыть терминал\n");
		close(tty);
		return -1;
	}
	else {
	for (i = 0; i <= x2; i++) {
		mt_gotoXY(x1 + i, y1);
		if (i == 1) {
			bc_printA("l");
			for (j = 2; j < y2; j++) bc_printA("q");
				bc_printA("k");
		}
		if (1 < i && i < x2) {
			bc_printA("x");
			for (j = 2; j < y2; j++) bc_printA(" ");
				bc_printA("x");
		}
		if (i == x2) {
			bc_printA("m");
			for (j = 2; j < y2; j++) bc_printA("q");
				bc_printA("j");
		}
	}
	close(tty);
	return 0;
	}
}

int bc_printbigchar(int *big, int x, int y, enum colors fg, enum colors bg) {
   int tty, i, j;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   else {
      mt_setfgcolor(fg);
      mt_setbgcolor(bg);
      for (j = 0; j < 2; j++) {
         for (i = 32; i > 0; i--) {
            if (i == 32) mt_gotoXY(x + 3 + 4 * j, y);
            if (i == 24) mt_gotoXY(x + 2 + 4 * j, y);
            if (i == 16) mt_gotoXY(x + 1 + 4 * j, y);
            if (i == 8) mt_gotoXY(x + 0 + 4 * j, y);
            if (((big[j] >> (i - 1)) & 0x1) == 1) bc_printA("a");
            else bc_printA(" ");
         }
      }
   }
   close(tty);
   return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value) {
   int tty, position;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   else {
      if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1)) {
         printf("Некорректные аргументы\n");
         return -1;
      }
      if (x <= 3) position = 0;
      else position = 1;
      x = x % 4;
      if (value == 0) big[position] = big[position] & ~(1 << (x * 8 + y));
      else big[position] = big[position] | 1 << (x * 8 + y);
   }
   close(tty);
   return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value) {
   int tty, position;
   tty = open("/dev/tty", O_RDWR);
   if (tty == -1) {
      printf("Невозможно открыть терминал\n");
      close(tty);
      return -1;
   }
   else {
      if ((x < 0) || (y < 0) || (x > 7) || (y > 7)) {
         printf("Некорректные координаты\n");
         return -1;
      }
      if (x <= 3) position = 0;
      else position = 1;
      x = x % 4;
      *value = (big[position] >> (x * 8 + y)) & 1;
   }
   close(tty);
   return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {
   int file = write(fd, &count, sizeof(count));
   if (file == -1) {
      printf("Ошибка записи в файл\n");
      return -1;
   }
   file = write(fd, big, count * (sizeof(int)) * 2);
   if (file == -1) {
      printf("Ошибка записи в файл\n");
      return -1;
   }
   return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count) {
   int n;
   int file = read(fd, &n, sizeof(n));
   if (file == -1 || (file != sizeof(n))) {
      printf("Ошибка чтения из файла\n");
      return -1;
   }
   int cnt = read(fd, big, need_count * sizeof(int) * 2);
   if (cnt == -1) {
      printf("Ошибка чтения из файла\n");
      *count = 0;
      return -1;
   }
   *count = cnt / (sizeof(int) * 2);
   return 0;
}


