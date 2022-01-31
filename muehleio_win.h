#ifndef MUEHLEIO_H_INCLUDED
#define MUEHLEIO_H_INCLUDED

#define ROWS                    7
#define COLS                    7
#define ASCII_ASMALL            97
#define ASCII_NULL              48
#define INVALID_POS             '+'
#define EMPTY                   '.'
#define X_AM_ZUG                '#'
#define O_AM_ZUG                '@'
#define SPIELSTEIN_X            'X'
#define SPIELSTEIN_O            'O'
#define PERS                    1 /*Person vs. Person*/
#define COMP                    2 /*Person vs. Computer*/
#define ERROR                   'E'
#define BUFFER_ERROR_FB         'y' /* ASCII- Wert größer als 100 um Verwechslungen zu verhindern*/
#define BUFFER_ERROR_GC         'z' /* ASCII- Wert größer als 100 um Verwechslungen zu verhindern*/
#define INVALIDMOVE_OOA         200002
#define INVALID_INPUT           1234567
#define JA                      1
#define NEIN                    0

#define PRINT_FELDLEER(x) (printf("Spieler %c, dieses Feld ist leider leer.\n", x))
#define PRINT_EINGABEWDH(x) (printf("Spieler %c, bitte versuche es noch einmal.\n", x))
#define PRINT_FELDBELEGT(x) (printf("Spieler %c, dieses Feld ist bereits belegt.\n", x))
#define PRINT_KEINFELD(x) (printf("Spieler %c, dieses Feld exisitiert nicht.\n", x))
#define PRINT_NICHTDEINSTEIN(x) (printf("Spieler %c, dieser Stein gehoert nicht dir.\n", x))
#define PRINT_DEINSTEIN(x) (printf("Spieler %c, dieser Stein gehoert dir.\n", x))
#define PRINT_ZUGVERBOTEN(x) (printf("Spieler %c, dieser Zug ist leider nicht erlaubt.\n", x))
#define PRINT_STEININMUEHLE(x) (printf("Spieler %c, dieser Stein ist in einer Muehle. Nimm einen anderen.\n", x))

void welcome(int pieces, int jumps_allowed); /*heißt den/die Spieler willkommen und erklärt kurz die Regeln*/

int flush_buff(void);

int pos_to_number(char input_pos[]); /*z.B. b4 meint board[3][1], also wird b4 zu 31*/
char* number_to_pos(int number_pos, char pos[]); /*31 wird zu zu b4 umgewandelt*/

char validinput_dir(void); /*fordert zur Richtungseingabe auf und überprüft auf Gültigkeit*/
int validinput_setpos(char player, int output); /*fordert zur Eingabe auf und prüft ob Eingabe eine Position beschreiben könnte*/
char validinput_gamemode(void); /*fordert zur Spielmodus-Eingabe auf und überprüft auf Richtigkeit*/

int pos_empty(int position, char board[ROWS][COLS]); /*prüft nur ob Spielfeld leer ist (einsetzen nach Überprüfung auf Gültigkeit)*/
int valid_pos(int position, char board[ROWS][COLS]); /*prüft nur ob Spielfeld gültig ist*/
int validmove_pos_dir(int number_pos, char input_dir, char board[ROWS][COLS]);/*überprüft nur ob Move ansich valide ist, nicht ob Spielfeld leer, Stein des Spielers, etc.*/
char who_col(int position, char board[ROWS][COLS]); /*wem gehört der Spielstein?*/

void remove_piece(int pos, char board[ROWS][COLS]); /*ändert Board, übergebene Position wird empty*/
int set_piece(char player, int old_pos, int new_pos, char board[ROWS][COLS]); /*ändert board, alte position wird empty, neue Position entweder X oder O*/

int all_pieces_stuck(char player, char board[ROWS][COLS]); /*prüft, ob alle Steine eines Spielers feststecken*/
int all_pieces_muehle(char player, char board[ROWS][COLS]); /*prüft, ob alle Steine eines Spielers in einer Mühle sind*/

char print_player(char player); /*wandelt den Spieler, der dran ist, in das Zeichen X/O um, um ihn auf der Kommandozeile anzusprechen*/

char rand_dir(int seed); /*generiert eine zufällige Richtung L/R/O/U*/
int rand_pos(int seed); /*generiert eine zufällige Position am Spielfeld*/

void initialize_board(char *board); /*initialisiert das Spielfeld: EMPTY auf gültige Felder, INVALID_POS auf ungültige Felder*/

void print_stone(char stone); /*gibt einen Spielstein in passender Farbe auf Kommandozeile aus; zusammen mit print_board wird so das Spielfeld ausgegeben*/
void print_board(char *board); /*gibt den Rest des Spielfeldes aus; zusammen mit print_stone wird so das Spielfeld ausgegeben*/

void glueckwunsch(char player); /*beglückwunscht den Gewinner des Spiels*/

#endif
