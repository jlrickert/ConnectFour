#ifndef CORE_H
#define CORE_H
#include <stdlib.h>

#define ROWS 6
#define COLS 7

struct board {
    int round;
    int whos_turn;
    int ai;
    char* playerOne;
    char* playerTwo;
    int mark[ROWS][COLS];
};

// Creates and returns a blank board
struct board new_board();

// Prints the board
void dsp_board(struct board* board);

// Selects the player and prompts for chip placement
void set_board(struct board* board);

// Checks and returns the winning player
// returns 0 if there is no winner
int check_board(struct board* board);

// Wins the game
void winner(char* player);

#endif
