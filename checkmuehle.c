#include "checkmuehle.h"

int muehle(int position, char board[ROWS][COLS], char am_zug)
{
	int rows = (position / 10);
	int cols = (position % 10);
	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int counter5 = 0;
	int i;
	int j;
	int k;


	if ( am_zug == X_AM_ZUG) { /*Schwarz ist am ZUG*/

		if (rows == MITTE && cols <= MITTE_MIN) { /*Prüft ob in Zeile 4 an den Spaltenindizes 1 bis 3 einme Mühle entstanden ist (oder ob sich ein weggenommener Stein des Gegners in einer Mühle befindet)*/
			for ( i = 0; i <= MITTE_MIN; i++) {
				if (board[rows][i] == SPIELSTEIN_B) {
					counter1++;
				}
			}
		} else if (rows == MITTE && cols >= MITTE_MAX) { /*Prüft ob in Zeile 4 an den Spaltenindizes 5 bis 7 eine Mühle entstanden ist (oder ob sich ein weggenommener Stein des Gegners in einer Mühle befindet)*/
			for ( i = MITTE_MAX; i < COLS; i++) {
				if (board[rows][i] == SPIELSTEIN_B) {
					counter1++;
				}
			}
		} else if (cols == MITTE && rows <= MITTE_MIN) {/*Prüft ob in Spalte 4 an den Zeilenindizes 1 bis 3 eine Mühle entstanden ist (oder ob sich ein weggenommener Stein des gegners in Mühle befindet)*/
			for ( i = 0; i <= MITTE_MIN; i++) {
				if (board[i][cols] == SPIELSTEIN_B) {
					counter1++;
				}
			}
		} else if (cols == MITTE && rows >= MITTE_MAX) { /*Prüft ob in Spalte 4 an den Zeilenindizes 5 bis 7 eine Mühle entstanden ist (oder ob sich ein weggenommener Stein des gegners in Mühle befindet)*/
			for ( i = MITTE_MAX; i < ROWS; i++) {
				if (board[i][cols] == SPIELSTEIN_B) {
					counter1++;
				}
			}
		}

		if (rows != MITTE && cols != MITTE) { /*Prüft ob an einem Eckpunkt eine Mühle entstanden ist (oder ob sich ein weggenommener Stein des gegners in Mühle befindet)*/
			for ( k = 0; k < COLS; k++) {
				if (board[rows][k] == SPIELSTEIN_B) {
					counter2++;
				}
			}

			for ( j = 0; j < ROWS; j++) {
				if (board[j][cols] == SPIELSTEIN_B) {
					counter3++;
				}
			}
		} else if(rows != MITTE) { /*Prüft ob an Zeilenindizes ungleich 3 eine Mühle entstanden ist (oder ob sich ein weggenommener Stein des gegners in Mühle befindet)*/
			for ( k = 0; k < COLS; k++) {
				if (board[rows][k] == SPIELSTEIN_B) {
					counter4++;
				}
			}
		} else if(cols != MITTE) { /*Prüft ob an Spaltenindizes ungleich 3 eine Mühle entstanden ist (oder ob sich ein weggenommener Stein des gegners in Mühle befindet)*/
			for ( j = 0; j < ROWS; j++) {
				if (board[j][cols] == SPIELSTEIN_B) {
					counter5++;
				}
			}
		}
	}

	if ( am_zug == O_AM_ZUG) { /*Weiß ist am Zug*/

		if (rows == MITTE && cols <= MITTE_MIN) { /*(...)*/
			for ( i = 0; i <= MITTE_MIN; i++) {
				if (board[rows][i] == SPIELSTEIN_W) {
					counter1++;
				}
			}
		} else if (rows == MITTE && cols >= MITTE_MAX) { /*(...)*/
			for ( i = MITTE_MAX; i < COLS; i++) {
				if (board[rows][i] == SPIELSTEIN_W) {
					counter1++;
				}
			}
		} else if (cols == MITTE && rows <= MITTE_MIN) { /*(...)*/
			for ( i = 0; i <= MITTE_MIN; i++) {
				if (board[i][cols] == SPIELSTEIN_W) {
					counter1++;
				}
			}
		} else if (cols == MITTE && rows >= MITTE_MAX) { /*(...)*/
			for ( i = MITTE_MAX; i < ROWS; i++) {
				if (board[i][cols] == SPIELSTEIN_W) {
					counter1++;
				}
			}
		}
		if (rows != MITTE && cols != MITTE) { /*(...)*/
			for ( k = 0; k < COLS; k++) {
				if (board[rows][k] == SPIELSTEIN_W) {
					counter2++;
				}
			}

			for ( j = 0; j < ROWS; j++) {
				if (board[j][cols] == SPIELSTEIN_W) {
					counter3++;
				}
			}
		} else if(rows != MITTE) {
			for ( k = 0; k < COLS; k++) { /*(...)*/
				if (board[rows][k] == SPIELSTEIN_W) {
					counter4++;
				}
			}
		} else if(cols != MITTE) {
			for ( j = 0; j < ROWS; j++) { /*(...)*/
				if (board[j][cols] == SPIELSTEIN_W) {
					counter5++;
				}
			}
		}
	}


	if (counter1 == MUEHLE_MAX || counter2 == MUEHLE_MAX || counter3 == MUEHLE_MAX || counter4 == MUEHLE_MAX || counter5 == MUEHLE_MAX) { /*Prüft ob in Zeile und Spalte von "newpos" eine Mühle entstanden ist*/
		return MUEHLE;
	} else {return KEINE_MUEHLE;}

}

void muehle_checker(char board[ROWS][COLS], char am_zug, int gamemode, int position, char *b_pointer, int *x_count, int *o_count, char whosecol)
{
	int stein_pos; /*Koordinaten des zu entfernenden Steines*/
	char gegner;
	char print_compmove[2];
	int check = muehle(position, board, am_zug);
	am_zug == O_AM_ZUG ? (gegner = X_AM_ZUG) : (gegner = O_AM_ZUG);
	if (check == MUEHLE || check == DOPPELMUEHLE) {

		if (!((am_zug == X_AM_ZUG) && (gamemode == COMP))) {
			printf("Spieler %c, du hast eine Muehle gelegt.\n", print_player(am_zug));
		}

		check = all_pieces_muehle(am_zug, board);
		if (check == JA) {
			printf("Leider kannst du keinen Stein wegnehmen, weil alle Steine des Gegners in einer Muehle sind.\n");
			return;
		}

		/*Problem: Programm überprüft nicht, ob weggenommener Stein in Mühle ist*/
		/*Problemlösung: Wir übergeben für muehle() die Position des Steines der entfernt werden soll, die "am_Zug"-variable des Gegners
		   sowie das board. Wenn der stein in Mühle ist folgt eine entsprechende Ausgabe und der Stein kann nicht entfternt werden*/
		do {
			if (gamemode == COMP && am_zug == X_AM_ZUG) {
				stein_pos = rand_pos(rand());
			} else {
				stein_pos = validinput_setpos(am_zug, 4);
			}

			if ((stein_pos == BUFFER_ERROR_FB) || (stein_pos == BUFFER_ERROR_GC) || (stein_pos == INVALID_INPUT)) {
				if (gamemode == COMP && am_zug == X_AM_ZUG) {
					continue;
				}
				PRINT_EINGABEWDH(print_player(am_zug));
				continue;
			}

			check = valid_pos(stein_pos, board);
			if (check == 1) {
				if (gamemode == COMP && am_zug == X_AM_ZUG) {
					continue;
				}
				PRINT_KEINFELD(print_player(am_zug));
				continue;
			}

			check = pos_empty(stein_pos, board);
			if (check == 0) {
				if (gamemode == COMP && am_zug == X_AM_ZUG) {
					continue;
				}
				PRINT_FELDLEER(print_player(am_zug));
				continue;
			}

			if (who_col(stein_pos, board) == whosecol) {
				if (gamemode == COMP && am_zug == X_AM_ZUG) {
					continue;
				}
				PRINT_DEINSTEIN(print_player(am_zug));
				continue;
			}
			if (muehle(stein_pos, board, gegner) == MUEHLE) {
				if (gamemode == COMP && am_zug == X_AM_ZUG) {
					continue;
				}
				PRINT_STEININMUEHLE(print_player(am_zug));
				continue;
			}
			break;
		} while (1);
		remove_piece(stein_pos, board);
		if (am_zug == X_AM_ZUG && gamemode == COMP) {
			printf("Der Computer hat deinen Stein von ");
			number_to_pos(stein_pos, print_compmove);
			printf(" entfernt, weil er eine Muehle gelegt hat.\n");
		}
		print_board(b_pointer);
		if (am_zug == O_AM_ZUG) {
			--(*x_count);
		} else {
			--(*o_count);
		}
	}
}
