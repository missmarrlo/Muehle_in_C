#include <stdio.h>
#include <stdlib.h>
#include "muehleio.h"
#include "checkmuehle.h"

void welcome(int pieces, int jumps_allowed)
{
        printf("Willkommen! \n\nMit diesem Programm kannst du den Brettspiel-Klassiker Muehle auf der Kommandozeile spielen. Es gelten die bekannten Muehle-Regeln. Beide Spieler haben zu Beginn jeweils %i Steine. Zu Beginn werden diese abwechselnd auf das Spielfeld gesetzt. Sobald alle Steine gesetzt sind, duerfen die Spieler abwechselnd einen Stein bewegen. ", pieces);
        printf("Entsteht hierbei eine Muehle, darf ein Stein des Gegners vom Spielfeld gestohlen werden. Ab %i Steinen darf gesprungen werden. Gewonnen hat, wer es zuerst schafft, dass der Gegner nur noch %i Steine auf dem Feld hat.\n\n", jumps_allowed, jumps_allowed - 1);
        printf("Damit das Spielbrett ganz auf der Kommandozeile zu sehen ist, sollte das Fenster mindestens so breit wie dieser Strich sein:\n----------------------------------------------\n\n");
        printf("Ein Spieler spielt mit den Steinen, die mit einem %c dargestellt werden, und der andere spielt mit denen, die mit einem %c dargestellt werden. Du kannst zwischen zwei Spielmodi waehlen. Du kannst zusammen mit einem anderen Spieler vor dem Computer spielen oder dich fuer ein Spiel gegen unseren hyperintelligenten Computer entscheiden. Hierbei spielt der Computer immer mit den %c-Steinen.\n\n", SPIELSTEIN_O, SPIELSTEIN_X, SPIELSTEIN_X);
}

int flush_buff(void) /*leert den Buffer*/
{
        int c;

        while (((c = getchar ()) != '\n') && (c != EOF))
        {}
        return c != EOF;
}

int pos_to_number(char input_pos[]) /*z.B. b4 meint board[3][1], also wird b4 zu 31*/
{
        int number = 0;
        number = (input_pos[0] - ASCII_ASMALL);  /*z.B Eingabe b in 1*/
        number += ((input_pos[1] - ASCII_NULL -1) * 10); /*z.B Eingabe 4 zu 30*/
        return number;
}

char* number_to_pos(int number_pos, char pos[]) /*31 zu b4*/
{
        pos[1] = ((number_pos / 10) + 1 + ASCII_NULL); /*z.B 3 zu 4*/
        pos[0] = ((number_pos % 10) + ASCII_ASMALL); /*z.B. 1 zu b*/
        printf("%c%c", pos[0], pos[1]);
        return pos;
}

char validinput_dir(void) /*Ueberprueft ob die Richtung korrekt eingegeben wurde*/
{
        char check;
        int letter;
        printf("In welche Richtung moechtest du deinen Spielstein bewegen? Waehle weise!\n");
        printf("'L' fuer links, 'R' fuer rechts, 'O' fuer oben, 'U' fuer unten.\n");
        letter = getchar();

        if(letter == EOF) {
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return BUFFER_ERROR_GC;
        }
        if((letter == 'L') || (letter == 'R') || (letter == 'O') || (letter == 'U')) {
                flush_buff();
                return letter;
        }else{
                printf("Tut mir leid, das habe ich nicht verstanden. Bitte ueberpruefe deine Eingabe und sag es mir nochmal.\n");
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return ERROR;
        }
}

int validinput_setpos(char player, int output) /*Je nach Spielphase anderer Output, gibt korrekte Position zurueck*/
{
        int letter = 0;
        int number = 0;
        char input[2];
        int input_number;
        char check;

        switch(output) {
        case 1: printf("Spieler %c, bitte sag mir, auf welches Feld du deinen Stein setzen moechtest.\n", print_player(player));
                break;
        case 2: printf("Spieler %c, bitte sag mir, welchen Stein du bewegen moechtest.\n", print_player(player));
                break;
        case 3: printf("Spieler %c, bitte sag mir, mit welchem Stein du springen moechtest.\n", print_player(player));
                break;
        case 4: printf("Spieler %c, bitte sag mir, welchen Stein des Gegners du entfernen moechtest.\n", print_player(player));
                break;
        }

        printf("Tu das in der Form 'b4', 'a1', 'g7' usw. und bestaetige mit Enter.\n");


        letter = getchar();

        if(letter == EOF) {
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return BUFFER_ERROR_GC;
        }
        if(('a' > letter) || (letter > 'g')) {
                printf("Deine Eingabe ist leider fehlerhaft.\n");
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return INVALID_INPUT;
        }

        number = getchar();
        if(number == EOF) {
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return BUFFER_ERROR_GC;
        }
        if((number < '1') || (number > '7')) {
                printf("Deine Eingabe ist leider fehlerhaft.\n");
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return INVALID_INPUT;
        }

        input[0] = letter;
        input[1] = number;

        input_number = pos_to_number(input);
        flush_buff();
        return input_number;
}

char validinput_gamemode(void)
{

        int i = 0;
        char check, input;

        printf("Druecke P und dann Enter, um gegen einen anderen Spieler zu spielen.\n");
        printf("Druecke C und dann Enter, um gegen den hyperintelligenten Computer zu spielen.\n");

        input = getchar();

        if(input == EOF) {
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return BUFFER_ERROR_GC;
        }
        if((input == 'P') || (input == 'C')) {
                check = flush_buff();
                if (check == EOF) { return BUFFER_ERROR_FB;}
                return input;
        }
        printf("Bitte ueberpruefe deine Eingabe und sag es mir nochmal.\n");
        check = flush_buff();
        if (check == EOF) { return BUFFER_ERROR_FB;}
        i++;

        return ERROR;
}

int pos_empty(int position, char board[ROWS][COLS])/*prueft nur ob Spielfeld leer ist (einsetzen nach Ueberpruefung auf Gueltigkeit), int position zuvor ueber pos_to_number*/

{
        int rows = (position / 10);
        int cols = (position % 10);
        if((board[rows][cols]) == EMPTY) {
                return 0;
        }
        return 1;
}

int valid_pos(int position, char board[ROWS][COLS]) /*prueft nur ob Spielfeld gueltig ist*/
{
        int rows = (position / 10);
        int cols = (position % 10);
        if((board[rows][cols]) != INVALID_POS) {
                return 0;
        }
        return 1;
}

int validmove_pos_dir(int number_pos, char input_dir, char board[ROWS][COLS]) /*Ueberprueft nur ob Move an sich valide ist, nicht ob Spielfeld leer, Stein des Spielers, etc.*/
{
        int rows = (number_pos / 10);
        int cols = (number_pos % 10);
        int i;

        if((number_pos == 32) && (input_dir == 'R')) {return INVALIDMOVE_OOA;} /*Sonderfälle für die Mitte des Spielfelds, sodass nicht "über die Mitte" gezogen werden kann*/
        if((number_pos == 34) && (input_dir == 'L')) {return INVALIDMOVE_OOA;}
        if((number_pos == 43) && (input_dir == 'O')) {return INVALIDMOVE_OOA;}
        if((number_pos == 23) && (input_dir == 'U')) {return INVALIDMOVE_OOA;}



        if(input_dir == 'R') {
                for(i = 1; i < 4; i++) { /*sieht die maximal 3 nächsten Spalteninträge nach rechts in der Zeile an, außer wir befinden uns schon außerhalb der Matrix*/
                        if((cols + i) >= COLS) {return INVALIDMOVE_OOA;}
                        if ((board[rows][cols + i] == EMPTY) || (board[rows][cols + i] == SPIELSTEIN_X) || (board[rows][cols + i] == SPIELSTEIN_O)  ) {
                                return ((rows * 10) + cols + i); /*gibt sich ergebende Position zurück, wenn diese valide ist*/
                        }
                }
        } else if(input_dir == 'L') {
                for(i = 1; i < 4; i++) {
                        if((cols - i) < 0) {return INVALIDMOVE_OOA;}
                        if((board[rows][cols - i] == EMPTY) || (board[rows][cols - i] == SPIELSTEIN_X) || (board[rows][cols -  i] == SPIELSTEIN_O)) {
                                return ((rows * 10) + cols - i);
                        }
                }
        }else if(input_dir == 'O') {
                for(i = 1; i < 4; i++) {
                        if((rows - i) < 0) {return INVALIDMOVE_OOA;}
                        if((board[rows - i][cols] == EMPTY) || (board[rows - i][cols] == SPIELSTEIN_X) || (board[rows - i][cols] == SPIELSTEIN_O)) {
                                return (((rows - i) * 10) + cols);
                        }
                }
        }else if(input_dir == 'U') {
                for(i = 1; i < 4; i++) {
                        if((rows + i) >= ROWS) {return INVALIDMOVE_OOA;}
                        if((board[rows + i][cols] == EMPTY) || (board[rows + i][cols] == SPIELSTEIN_X) || (board[rows + i][cols] == SPIELSTEIN_O)) {
                                return (((rows + i) * 10) + cols);
                        }
                }
        }
        return INVALIDMOVE_OOA;
}

char who_col(int position, char board[ROWS][COLS]) /*wem gehoert der Spielstein?*/
{
        int rows = (position / 10);
        int cols = (position % 10);
        if((board[rows][cols]) == SPIELSTEIN_X) {
                return SPIELSTEIN_X;
        }else if((board[rows][cols]) == SPIELSTEIN_O) {
                return SPIELSTEIN_O;
        }
        return ERROR;
}

void remove_piece(int pos, char board[ROWS][COLS]) /*Aendert Board-Eintrag an uebergebener Position zu EMPTY*/
{
        int rows = (pos / 10);
        int cols = (pos % 10);
        board[rows][cols] = EMPTY;
}

int set_piece(char player, int old_pos, int new_pos, char board[ROWS][COLS])
{
        int rows = (old_pos / 10);
        int cols = (old_pos % 10);
        board[rows][cols] = EMPTY;
        rows = (new_pos / 10);
        cols = (new_pos % 10);
        if (player == X_AM_ZUG) {
                board[rows][cols] = SPIELSTEIN_X;
                return 0;
        }else if (player == O_AM_ZUG) {
                board[rows][cols] = SPIELSTEIN_O;
                return 0;
        }
        return 1;
}

int all_pieces_stuck(char player, char board[ROWS][COLS]) /*iteriert durch alle Steine der Farbe in alle moegliche Richtungen und prueft ob gueltiger Zug moeglich waere*/
{
        int i, j, k, movevalid, posempty;
        char piece;
        char directions[] = {'L', 'R', 'O', 'U'};
        if (player == X_AM_ZUG) {piece = SPIELSTEIN_X;}
        if (player == O_AM_ZUG) {piece = SPIELSTEIN_O;}
        for (i = 0; i < ROWS; i++) {
                for (j = 0; j < COLS; j++) {
                        if(board[i][j] == piece) { /*ueberprueft alle Spielsteine des uebergebenen Spielers*/
                                for(k = 0; k < 4; k++) { /*ueberprueft alle Richtungen*/
                                        movevalid = validmove_pos_dir((i*10 + j), directions[k], board);
                                        if (movevalid != INVALIDMOVE_OOA) {
                                                posempty = pos_empty(movevalid, board);
                                                if (posempty == 0) {
                                                        return NEIN; /*Spieler steckt nicht fest*/
                                                }
                                        }
                                }
                        }
                }
        }
        return JA; /*Spieler steckt fest*/
}

int all_pieces_muehle(char player, char board[ROWS][COLS]) /*ueberprueft ob alle Steine des Gegeners des uebergebenen Spielers in Muehle sind*/
{
        int i, j, muehlecheck;
        char piece, tempplayer;
        if (player == X_AM_ZUG) {piece = SPIELSTEIN_O; tempplayer = O_AM_ZUG;}
        if (player == O_AM_ZUG) {piece = SPIELSTEIN_X; tempplayer = X_AM_ZUG;}
        for (i = 0; i < ROWS; i++) {
                for (j = 0; j < COLS; j++) {
                        if(board[i][j] == piece) {
                                muehlecheck = muehle((i * 10 + j), board, tempplayer);
                                if(muehlecheck == KEINE_MUEHLE) {
                                        return NEIN; /*nicht alle Spielsteine in Muehle*/
                                }
                        }
                }
        }
        return JA; /*alle Spielsteine in Muehle*/
}

char print_player(char player)
{
        if (player == X_AM_ZUG) {
                return SPIELSTEIN_X;
        } else {
                return SPIELSTEIN_O;
        }
}

char rand_dir(int seed) /*Aufruf: rand_dir(rand()); vorher einmal srand(time(NULL)) setzen*/
{
        seed = seed % 4;
        switch (seed) {
        case 0: return 'L';
        case 1: return 'R';
        case 2: return 'O';
        case 3: return 'U';
        }
        return ERROR;
}

int rand_pos(int seed) /*Aufruf: rand_pos(rand()); vorher einmal srand(time(NULL)) setzen*/
{
        seed = seed % 24;
        switch(seed) {
        case 0:  return 00;
        case 1:  return 03;
        case 2:  return 06;
        case 3:  return 11;
        case 4:  return 13;
        case 5:  return 15;
        case 6:  return 22;
        case 7:  return 23;
        case 8:  return 24;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 32;
        case 12: return 34;
        case 13: return 35;
        case 14: return 36;
        case 15: return 42;
        case 16: return 43;
        case 17: return 44;
        case 18: return 51;
        case 19: return 53;
        case 20: return 55;
        case 21: return 60;
        case 22: return 63;
        case 23: return 66;
        }
        return ERROR;
}

void initialize_board(char *board)
{
        int i = 0;
        *(board) = EMPTY;
        *(board + 3) = EMPTY;
        *(board + 6) = EMPTY;
        *(board + 8) = EMPTY;
        *(board + 10) = EMPTY;
        *(board + 12) = EMPTY;
        *(board + 16) = EMPTY;
        *(board + 17) = EMPTY;
        *(board + 18) = EMPTY;
        *(board + 21) = EMPTY;
        *(board + 22) = EMPTY;
        *(board + 23) = EMPTY;
        *(board + 25) = EMPTY;
        *(board + 26) = EMPTY;
        *(board + 27) = EMPTY;
        *(board + 30) = EMPTY;
        *(board + 31) = EMPTY;
        *(board + 32) = EMPTY;
        *(board + 36) = EMPTY;
        *(board + 38) = EMPTY;
        *(board + 40) = EMPTY;
        *(board + 42) = EMPTY;
        *(board + 45) = EMPTY;
        *(board + 48) = EMPTY;
        while (i <= 48 + 1) {
                if (*(board + i) != EMPTY) {
                        *(board + i) = INVALID_POS;
                }
                ++i;
        }
}

void print_stone(char stone)
{
        if (stone == SPIELSTEIN_X) {
                printf( "%c", stone);
        } else {
                if (stone == SPIELSTEIN_O) {
                        printf("%c", stone);
                }
                else {
                        printf("%c", stone);
                }
        }
}

void print_board(char *board)
{
        printf("\n       a     b    c    d    e    f     g\n\n");
        printf(" 1     ");
        print_stone(*(board));
        printf("---------------");
        print_stone(*(board + 3));
        printf("---------------");
        print_stone(*(board + 6));
        printf("     1\n");
        printf("       |               |               |\n");
        printf(" 2     |     ");
        print_stone(*(board + 8));
        printf("---------");
        print_stone(*(board + 10));
        printf("---------");
        print_stone(*(board + 12));
        printf("     |     2\n");
        printf("       |     |         |         |     |\n");
        printf(" 3     |     |    ");
        print_stone(*(board + 16));
        printf("----");
        print_stone(*(board + 17));
        printf("----");
        print_stone(*(board + 18));
        printf("    |     |     3\n");
        printf("       |     |    |         |    |     |\n");
        printf(" 4     ");
        print_stone(*(board + 21));
        printf("-----");
        print_stone(*(board + 22));
        printf("----");
        print_stone(*(board + 23));
        printf("         ");
        print_stone(*(board + 25));
        printf("----");
        print_stone(*(board + 26));
        printf("-----");
        print_stone(*(board + 27));
        printf("     4\n");
        printf("       |     |    |         |    |     |\n");
        printf(" 5     |     |    ");
        print_stone(*(board + 30));
        printf("----");
        print_stone(*(board + 31));
        printf("----");
        print_stone(*(board + 32));
        printf("    |     |     5\n");
        printf("       |     |         |         |     |\n");
        printf(" 6     |     ");
        print_stone(*(board + 36));
        printf("---------");
        print_stone(*(board + 38));
        printf("---------");
        print_stone(*(board + 40));
        printf("     |     6\n");
        printf("       |               |               |\n");
        printf(" 7     ");
        print_stone(*(board + 42));
        printf("---------------");
        print_stone(*(board + 45));
        printf("---------------");
        print_stone(*(board + 48));
        printf("     7\n\n");
        printf("       a     b    c    d    e    f     g\n\n");
}

void glueckwunsch(char player)
{
        printf( "          _     _ _____ _      _ _      _ _ _  \n");
        printf( "         \\ \\   / /  ____\\ \\   / /\\ \\   / / | | \n");
        printf( "          \\ \\_/ /| |__   \\ \\_/ /  \\ \\_/ /| | | \n");
        printf( "           \\   / |  __|   \\   /    \\   / | | | \n");
        printf( "            | |  | |____   | |      | |  |_|_| \n");
        printf( "            |_|  |______|  |_|      |_|  (_|_) \n");
        printf("\n\n");

        printf("Das Spiel ist vorbei und Spieler %c hat gewonnen! Gut gespielt!\n", print_player(player));
}
