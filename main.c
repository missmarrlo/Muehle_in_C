#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "muehleio.h"
#include "checkmuehle.h"

#define PIECES 9 /*Anzahl der Steine zu Beginn des Spiels*/
#define JUMPS_ALLOWED 3 /*Anzahl der Steine, sodass man springen darf*/

int main(void)
{
        char board[ROWS][COLS];
        char *b_pointer = &board[0][0];
        int x_count = PIECES;
        int o_count = PIECES;
        int x_yettoset = PIECES;
        int o_yettoset = PIECES;
        int gamemode, counter, position, check, position1, position2, yettoset, am_zug_counter, stuck;
        char enter_gamemode, direction, am_zug, whosecol, winner;
        char print_compmove[2];
        srand(time(NULL));

        initialize_board(b_pointer);

        welcome(PIECES, JUMPS_ALLOWED);

        enter_gamemode = validinput_gamemode();
        while (enter_gamemode == ERROR) {
                enter_gamemode = validinput_gamemode();
        }

        if (enter_gamemode == BUFFER_ERROR_FB || enter_gamemode == BUFFER_ERROR_GC) {
                return 1;
        }

        enter_gamemode == 'P' ? (gamemode = PERS) : (gamemode = COMP);
        print_board(b_pointer);

        /*PHASE 1 (SETZPHASE):*/
        counter = 1;
        while (o_yettoset > 0 || x_yettoset > 0) {
                /*Diese Schleife laeuft abwechselnd für Spieler O und X (für ungerade/gerade Zahlen), damit der Codeteil nicht doppelt ist.*/
                /*Beim Spielmodus C ist der Computer der Spieler X.*/
                counter % 2 != 0 ? (yettoset = o_yettoset) : (yettoset = x_yettoset);
                counter % 2 != 0 ? (am_zug = O_AM_ZUG) : (am_zug = X_AM_ZUG);
                counter % 2 != 0 ? (whosecol = SPIELSTEIN_O) : (whosecol = SPIELSTEIN_X);
                if (yettoset > 0) {
                        do {
                                if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                        position = rand_pos(rand());
                                } else {
                                        position = validinput_setpos(am_zug, 1);
                                }

                                if ((position == BUFFER_ERROR_FB) || (position == BUFFER_ERROR_GC) || (position == INVALID_INPUT)) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_EINGABEWDH(am_zug);
                                        continue;
                                }

                                check = valid_pos(position, board);
                                if (check == 1) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_KEINFELD(print_player(am_zug));
                                        continue;
                                }

                                check = pos_empty(position, board);
                                if (check == 1) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_FELDBELEGT(print_player(am_zug));
                                        continue;
                                }

                                break;
                        } while(1);
                        set_piece(am_zug, position, position, board);
                        --yettoset;

                        counter % 2 != 0 ? (o_yettoset = yettoset) : (x_yettoset = yettoset);
                        ++counter;
                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                printf("Der Computer hat seinen Stein auf ");
                                number_to_pos(position, print_compmove);
                                printf(" gesetzt.\n");
                        }
                        print_board(b_pointer);

                        /*Ueberpruefen auf Muehle:*/
                        muehle_checker(board, am_zug, gamemode, position, b_pointer, &x_count, &o_count, whosecol);
                }
        }
        /*PHASEN 2 UND 3 (ZIEH- UND SPRUNGPHASE):*/
        printf("Alle Spielsteine wurden am Brett platziert. Ab sofort duerfen die Steine abwechselnd um ein Feld verschoben werden. Besitzt ein Spieler nur noch %i Steine, so darf gesprungen werden.\n\n", JUMPS_ALLOWED);
        counter = 1;
        while (x_count >= JUMPS_ALLOWED && o_count >= JUMPS_ALLOWED) {
                counter % 2 != 0 ? (am_zug_counter = o_count) : (am_zug_counter = x_count);
                counter % 2 != 0 ? (am_zug = O_AM_ZUG) : (am_zug = X_AM_ZUG);
                counter % 2 != 0 ? (whosecol = SPIELSTEIN_O) : (whosecol = SPIELSTEIN_X);
                stuck = all_pieces_stuck(am_zug, board);
                if (stuck == JA) {
                        printf("Sorry, Spieler %c, aber du steckst fest! Damit ist das Spiel zu Ende.\n", print_player(am_zug));
                        break;
                }
                /*Phase 2 (Ziehphase)*/
                if (am_zug_counter > JUMPS_ALLOWED) {
                        do {
                                if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                        position1 = rand_pos(rand());
                                } else {
                                        position1 = validinput_setpos(am_zug, 2);
                                }

                                if ((position1 == BUFFER_ERROR_FB) || (position1 == BUFFER_ERROR_GC) || (position1 == INVALID_INPUT)) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_EINGABEWDH(print_player(am_zug));
                                        continue;
                                }

                                check = pos_empty(position1, board);
                                if (check == 0) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_FELDLEER(print_player(am_zug));
                                        continue;
                                }

                                if (who_col(position1, board) != whosecol) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_NICHTDEINSTEIN(print_player(am_zug));
                                        continue;
                                }

                                if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                        direction = rand_dir(rand());
                                } else {
                                        direction = validinput_dir();
                                }

                                if (direction == BUFFER_ERROR_FB || direction == BUFFER_ERROR_GC || direction == ERROR) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_EINGABEWDH(print_player(am_zug));
                                        continue;
                                }

                                position2 = validmove_pos_dir(position1, direction, board);

                                if (position2 == INVALIDMOVE_OOA) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_ZUGVERBOTEN(print_player(am_zug));
                                        continue;
                                }

                                check = pos_empty(position2, board);
                                if (check == 1) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_FELDBELEGT(print_player(am_zug));
                                        continue;
                                }

                                check = valid_pos(position2, board);
                                if (check == 1) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_ZUGVERBOTEN(print_player(am_zug));
                                        continue;
                                }

                                if (position2 == INVALIDMOVE_OOA) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_ZUGVERBOTEN(print_player(am_zug));
                                        continue;
                                }

                                break;
                        } while(1);
                        set_piece(am_zug, position1, position2, board);
                }

                /*Phase 3 (Sprungphase)*/
                if (am_zug_counter == JUMPS_ALLOWED) {
                        do {
                                if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                        position1 = rand_pos(rand());
                                } else {
                                        position1 = validinput_setpos(am_zug, 3);
                                }

                                if ((position1 == BUFFER_ERROR_FB) || (position1 == BUFFER_ERROR_GC) || (position1 == INVALID_INPUT)) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_EINGABEWDH(print_player(am_zug));
                                        continue;
                                }

                                check = pos_empty(position1, board);
                                if (check == 0) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_FELDLEER(print_player(am_zug));
                                        continue;
                                }

                                if (who_col(position1, board) != whosecol) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_NICHTDEINSTEIN(print_player(am_zug));
                                        continue;
                                }

                                if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                        position2 = rand_pos(rand());
                                } else {
                                        position2 = validinput_setpos(am_zug, 1);
                                }

                                if ((position2 == BUFFER_ERROR_FB) || (position2 == BUFFER_ERROR_GC) || (position2 == INVALID_INPUT)) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_EINGABEWDH(print_player(am_zug));
                                        continue;
                                }

                                check = pos_empty(position2, board);
                                if (check == 1) {
                                        if (gamemode == COMP && am_zug == X_AM_ZUG) {
                                                continue;
                                        }
                                        PRINT_FELDBELEGT(print_player(am_zug));
                                        continue;
                                }

                                break;
                        } while (1);
                        set_piece(am_zug, position1, position2, board);
                }
                ++counter;
                if (gamemode == COMP && am_zug == X_AM_ZUG) {
                        printf("Der hyperintelligente Computer hat einen Stein von ");
                        number_to_pos(position1, print_compmove);
                        printf(" auf ");
                        number_to_pos(position2, print_compmove);
                        printf(" gesetzt.\n");
                }
                print_board(b_pointer);
                muehle_checker(board, am_zug, gamemode, position2, b_pointer, &x_count, &o_count, whosecol);
        }

        /* Spiel ist zu Ende*/
        if (stuck == JA) {
                am_zug == O_AM_ZUG ? (winner = X_AM_ZUG) : (winner = O_AM_ZUG);
        } else {
                o_count < JUMPS_ALLOWED ? (winner = X_AM_ZUG) : (winner = O_AM_ZUG);
        }

        glueckwunsch(winner);

        return 0;
}
