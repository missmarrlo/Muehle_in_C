#ifndef CHECKMUEHLE_H_INCLUDED
#define CHECKMUEHLE_H_INCLUDED

/*Bibliotheken*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "muehleio.h"

/*Symbolische Konstanten*/
#define ROWS 7
#define COLS 7
#define MUEHLE 100004
#define DOPPELMUEHLE 100005
#define KEINE_MUEHLE 100006
#define SPIELSTEIN_B 'X'
#define SPIELSTEIN_W 'O'
#define X_AM_ZUG '#'
#define O_AM_ZUG '@'
#define MUEHLE_MAX 3
#define MITTE 3
#define MITTE_MIN 2
#define MITTE_MAX 4
#define ABSTAND_A 3
#define ABSTAND_M 2
#define ABSTAND_I 1
#define STUCK 100007
#define FREE 100008
#define INVALID_MOVE_M 100009


/*Funktionen*/
int muehle(int position, char board[ROWS][COLS], char am_zug);
void muehle_checker(char board[ROWS][COLS], char am_zug, int gamemode, int position, char *b_pointer, int *x_count, int *o_count, char whosecol);

#endif
