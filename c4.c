#include "core.h"
#include "helper.h"
#include "multiplayer.h"
#include "appinfo.h"


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
