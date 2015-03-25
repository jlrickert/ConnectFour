#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "c4.h"
#include "helper.h"


struct board
new_board()
{
    struct board board;

    // get player names
    printf("Enter name of Player One (AI for computer player): ");
    get_str(&(board.playerOne));
    clear_lines(0);
    printf("Enter name of Player Two (AI for computer player): ");
    get_str(&(board.playerTwo));

    // Generate blank board
    clear_lines(2);
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board.mark[row][col] = 0;
        }
    }
    srand(time(NULL));
    board.whos_turn = (rand() % 2) + 1;
    board.round = 0;

    return board;
}

void
dsp_board(struct board* pBoard)
{
    char* locale;
    locale = setlocale(LC_ALL, "en_US.UTF-8");

    static bool first_run = true;
    if (!first_run) {
        clear_lines(9);
    }

    printf("%ls", L" 1 2 3 4 5 6 7\n");
    printf("%ls", L"╔═╤═╤═╤═╤═╤═╤═╗\n");
    for (int row = 0; row < ROWS; row++) {
        if (row == 0) printf("%ls", L"║");
        for (int col = 0; col < COLS; col++) {
            printf("%ls", mark[pBoard->mark[row][col]]);
            col == 6 ? printf("%ls", L"║") : printf("%ls", L"│");
        }
        row < 5
            ? printf("\n%ls", L"║")
            : printf("%ls", L"\n╚═╧═╧═╧═╧═╧═╧═╝\n");
    }

    first_run = false;
}


void
set_board(struct board* pBoard)
{
    int col, row;
    static int filled_rows[COLS];
    string name = (pBoard->whos_turn == 1) ? pBoard->playerOne : pBoard->playerTwo;

    printf("%s please enter Column to place %ls: ", name, mark[pBoard->whos_turn]);
    loop {
        col = get_int() - 1;
        if (col < 0 || col > (COLS - 1)) {
            clear_lines(1);
            printf("Column doesnt exist.  Please renter: ");
            continue;
        } else if (filled_rows[col] == 1) { // is || short circuited in c?
            clear_lines(1);
            printf("Column is already filled: ");
            continue;
        }

        // check if column is not filled
        for (int i = ROWS - 1; i >= 0; i--) {
            if (pBoard->mark[i][col] == 0) {
                row = i;
                goto setmark;
            } else if (i == 0) {
                filled_rows[col] = 1;
                clear_lines(1);
                printf("Column is already filled: ");
            }
        }
    }

    setmark:
    clear_lines(1);
    pBoard->mark[row][col] = pBoard->whos_turn;
    pBoard->whos_turn = (pBoard->whos_turn == 1) ? 2 : 1;
    pBoard->round++;
}

void
winner(string player)
{
    printf("Congratulations %s\n", player);
    exit(0);
}

inline static int
get_opponent(int player){
    switch (player) {
    case 2:
        return 1;
    case 1:
        return 2;
    default:
        return 0;
    }
}

static int
check_row(struct board* pBoard)
{
    static int row_select[ROWS];
    static int row_mark[ROWS];
    if (pBoard->round < 5) {
        memset(row_select, 0, sizeof(int[ROWS]));
        memset(row_mark,   0, sizeof(int[ROWS]));
    }

    // check rows
    for (int i = 0; i < ROWS; i++) {
        row_start:
        switch (row_select[i]) {
        case 2:
            break;
        case 1:
            if ((pBoard->mark[i][2] == get_opponent(row_mark[i])) &&
                (pBoard->mark[i][4] == get_opponent(row_mark[i]))) {
                row_select[i] = 2;
                goto row_start;
            } else {
                for (int j = 0; j < 4; j++) {
                    if (pBoard->mark[i][j]   == row_mark[i] &&
                        pBoard->mark[i][j+1] == row_mark[i] &&
                        pBoard->mark[i][j+2] == row_mark[i] &&
                        pBoard->mark[i][j+3] == row_mark[i]) {
                        return row_mark[i];
                    }
                }
                break;
            }
        default:
            if (pBoard->mark[i][3] != 0) {
                row_mark[i] = pBoard->mark[i][3];
                row_select[i] = 1;
                goto row_start;
            } else {
                break;
            }
        }
    }
    return 0;
}

static int
check_col(struct board* pBoard)
{
    static int col_select[COLS];
    static int col_mark[ROWS];

    if (pBoard->round < 5) {
        memset(col_select, 0, sizeof(int[COLS]));
        memset(col_mark,   0, sizeof(int[COLS]));
    }

    for (int i = 0; i < COLS; i++) {
        col_start:
        switch (col_select[i]) {
        case 4:
            break;
        case 3:
            if (pBoard->mark[0][i] == 0) {
                break;
            } else if (pBoard->mark[0][i] == col_mark[i]) {
                return col_mark[i];
            } else {
                col_select[i] = 4;
            }
        case 2:
            if (pBoard->mark[1][i] == 0) {
                break;
            } else if (pBoard->mark[1][i] == col_mark[i]) {
                return col_mark[i];
            } else {
                col_select[i] = 3;
                goto col_start;
            }
        case 1:
            if (pBoard->mark[5][i] == col_mark[i] &&
                    pBoard->mark[4][i] == col_mark[i]) {
                return col_mark[i];
            } else if (pBoard->mark[4][i] == col_mark[i]) {
                col_select[i] = 2;
                goto col_start;
            } else {
                col_select[i] = 3;
                goto col_start;
            }
        default:
            if (pBoard->mark[2][i] == 0) {
                break;
            } else if (pBoard->mark[3][i] == pBoard->mark[2][i]) {
                col_mark[i] = pBoard->mark[2][i];
                col_select[i] = 1;
                goto col_start;
            } else {
                col_select[i] = 4;
                goto col_start;
            }
        }
    }
    return 0;
}

static int
check_diagnal(struct board* pBoard)
{
    static int d_invalid[6];
    static int d_mark[6];
    int row_order[] = {5,0,3,3,2,2};
    int col_order[] = {3,3,2,4,2,4};
    int row, col;
    int mRow, mCol, mod;
    int count;
    int marker;

    if (pBoard->round < 10) {
        return 0;
    } else if (pBoard->round < 11) {
        memset(d_invalid,  0, sizeof(int[6]));
        memset(d_mark,     0, sizeof(int[6]));
    }

    // check valid diagnals
    for (int i = 0; i < 6; i++) {
        row = row_order[i];
        col = col_order[i];

        if (d_invalid[i] || pBoard->mark[row][col] == 0) {
            continue;
        } else if (d_mark[i] == 0) {
            d_mark[i] = pBoard->mark[row_order[i]][col_order[i]];
        }

        // NW to SE
        mod = (row < col) ? row : col;
        mRow = row - mod;
        mCol = col - mod;
        count = 0;
        while (mRow < ROWS && mCol < COLS) {
            if (pBoard->mark[mRow][mCol] == d_mark[i]) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) return d_mark[i];
            mRow++; mCol++;
        }

        // SW to NE
        mod = (5 - row < col) ? 5 - row : col;
        mRow = row + mod;
        mCol = col - mod;
        count = 0;
        while (mRow < ROWS && mCol < COLS) {
            if (pBoard->mark[mRow][mCol] == d_mark[i]) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) return d_mark[i];
            mRow--; mCol++;
        }
    }
    return 0;
}

int
check_board(struct board* pBoard)
{
    int row_checked = 0;
    int col_checked = 0;
    int diagnal_checked = 0;

    if (pBoard->round < 4) return 0;
    col_checked = check_col(pBoard);
    row_checked = check_row(pBoard);
    diagnal_checked = check_diagnal(pBoard);

    if (row_checked) {
        return row_checked;
    } else if (col_checked) {
        return col_checked;
    } else if (diagnal_checked) {
        return diagnal_checked;
    } else {
        return 0;
    }
}

int
main(int argc, char* argv[])
{
    struct board board = new_board();
    string player;
    int have_winner = 0;

    dsp_board(&board);

    loop {
        set_board(&board);
        dsp_board(&board);
        have_winner = check_board(&board);
        if (have_winner) {
            player = (have_winner == 1) ? board.playerOne : board.playerTwo;
            winner(player);
            break;
        }
    }

    return 0;
}
