#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <iostream>
#include <algorithm>
//#include "vertex.h"


class gameboard
{

private:

    char statuses[13][17];
    struct rowcol {
        int col = -1;
        int row = -1;
        bool operator == (const rowcol &rc) {
            if (col == rc.col && row == rc.row) {
                return true;
            }
            return false;
        }
    };
    rowcol adjacents[13][17][6];
    void set_tiles();
    void set_adjacents(int column, int row);
    char currplayer = 'R';
    bool is_empty_opposite(int bc, int br, int ec, int er);
    int rounds = 0;
    rowcol top_pos[10] = {{6,0},{6,1},{7,1},{5,2},{6,2},{7,2},{5,3},{6,3},{7,3},{8,3}};
    rowcol bot_pos[10] = {{6,16},{6,15},{7,15},{5,14},{6,14},{7,14},{5,13},{6,13},{7,13},{8,13}};


public:

    gameboard();
    ~gameboard();
    char victory_satisfied();
    bool leftover_pieces(int round, char player);
    bool is_adjacent(int bc, int br, int ec, int er);
    void init_board();
//    std::vector<vertex> nearby_vertices(vertex v);
    void next_turn();
    bool make_move(char player, int bc, int br, int ec, int er);
};

#endif // GAMEBOARD_H
