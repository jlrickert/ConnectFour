#ifndef C4_H
#define C4_H

#define ROWS 6
#define COLS 7


wchar_t mark[3][28] = {
    {L"О"},
    {L"\x1B[34m█\x1B[0m"},
    {L"\x1B[31m█\x1B[0m"}
};

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
