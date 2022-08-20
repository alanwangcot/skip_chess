#include "gameboard.h"
#include <vector>

gameboard::gameboard()
{
    init_board();
}

//sets up the base state of the board
void gameboard::set_tiles() {
    // Set all to N, and sets positions
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 17; j++) {
            statuses[i][j] = 'N';
        }
    }

    // Set pieces
    //top and bottom row
    statuses[6][0] = 'R';
    statuses[6][16] = 'B';

    //second and second last row
    statuses[6][1] = 'R';
    statuses[7][1] = 'R';
    statuses[6][15] = 'B';
    statuses[7][15] = 'B';

    //third and third last row
    statuses[5][2] = 'R';
    statuses[6][2] = 'R';
    statuses[7][2] = 'R';
    statuses[5][14] = 'B';
    statuses[6][14] = 'B';
    statuses[7][14] = 'B';

    //fourth and fourth last row
    statuses[5][3] = 'R';
    statuses[6][3] = 'R';
    statuses[7][3] = 'R';
    statuses[8][3] = 'R';
    statuses[5][13] = 'B';
    statuses[6][13] = 'B';
    statuses[7][13] = 'B';
    statuses[8][13] = 'B';

    // set empty spaces
    for (int i = 0; i < 13; i++) {
        statuses[i][4] = 'E';
        statuses[i][12] = 'E';

        statuses[i][5] = 'E';
        statuses[i][11] = 'E';

        statuses[i][6] = 'E';
        statuses[i][10] = 'E';

        statuses[i][7] = 'E';
        statuses[i][9] = 'E';

        statuses[i][8] = 'E';
    }

    // re-set overriden -1 tiles
        statuses[0][5] = 'N';
        statuses[0][6] = 'N';
        statuses[6][12] = 'N';
        statuses[0][7] = 'N';
        statuses[1][7] = 'N';
        statuses[12][7] = 'N';
        statuses[0][8] = 'N';
        statuses[1][8] = 'N';
        statuses[12][8] = 'N';
        statuses[11][8] = 'N';
        statuses[0][9] = 'N';
        statuses[1][9] = 'N';
        statuses[12][9] = 'N';
        statuses[0][10] = 'N';
        statuses[12][10] = 'N';
        statuses[0][11] = 'N';
}

void gameboard::set_adjacents(int col, int row) {

    int counter = 0;
    if ((col - 1) >= 0) {
        if (statuses[col - 1][row] != 'N') {
            adjacents[col][row][counter].col = col - 1;
            adjacents[col][row][counter].row = row;
            counter++;
        }
    }
    if ((col + 1) < 13) {
        if (statuses[col + 1][row] != 'N') {
            adjacents[col][row][counter].col = col + 1;
            adjacents[col][row][counter].row = row;
            counter++;
        }
    }
    // even rows
    if (row % 2 == 0) {
        // row above
        if ((row - 1) >= 0 && statuses[col][row -1] != 'N') {
            adjacents[col][row][counter].col = col;
            adjacents[col][row][counter].row = row - 1;
            counter++;
            if ((col + 1) < 13 && statuses[col + 1][row - 1] != 'N' ) {
                adjacents[col][row][counter].col = col + 1;
                adjacents[col][row][counter].row = row - 1;
                counter++;
            }
        }
        // row below
        if ((row + 1) < 17 && statuses[col][row + 1] != 'N') {
            adjacents[col][row][counter].col = col;
            adjacents[col][row][counter].row = row + 1;
            if ((col + 1) < 13 && statuses[col + 1][row + 1] != 'N') {
                adjacents[col][row][counter].col = col + 1;
                adjacents[col][row][counter].row = row + 1;
                counter++;
            }
        }

    }

    //odd rows
    if (row % 2 != 0) {
        // row above
        if ((row - 1) >= 0 && statuses[col][row - 1] != 'N') {
            adjacents[col][row][counter].col = col;
            adjacents[col][row][counter].row = row - 1;
            counter++;
            if ((col - 1) >= 0 && statuses[col - 1][row -1] != 'N') {
                adjacents[col][row][counter].col = col - 1;
                adjacents[col][row][counter].row = row - 1;
                counter++;
            }
        }
        // row below
        if ((row + 1) < 17 && statuses[col][row + 1] != 'N') {
            adjacents[col][row][counter].col = col;
            adjacents[col][row][counter].row = row + 1;
            counter++;
            if ((col - 1) >= 0 && statuses[col - 1][row + 1] != 'N') {
                adjacents[col][row][counter].col = col - 1;
                adjacents[col][row][counter].row = row + 1;
                counter++;
            }
        }
    }
}

void gameboard::next_turn() {
    if (this->currplayer == 'R') {
        currplayer = 'B';

    } else {
        currplayer = 'R';
        rounds++;
    }
}

bool gameboard::is_adjacent(int bc, int br, int ec, int er) {
    for (int i = 0; i < 6; i++) {
        if (adjacents[bc][br][i].col == ec && adjacents[bc][br][i].row == er) {
            return true;
        }
    }
    return false;
}

// given two adjacents of a position, see if they are opposite each other
bool gameboard::is_empty_opposite(int bc, int br, int ec, int er) {
    if (statuses[ec][er] != 'E') {
        return false;
    }
    // case row is same
    if (br == er) {
        if (abs(bc - ec) == 2) {
            return true;
        }
    }
    // rows are not touching
    if (abs(br - er) == 2) {
            if (abs(bc - ec) == 1) {
                return true;
            }
    }
    return false;
}

// will only return true if move is valid
bool gameboard::make_move(char player, int bc, int br, int ec, int er) {
    // if player tries to move piece that isn't theirs
    if (player != statuses[bc][br]) {
        return false;
    }
    // if adjacent and empty space
    if (is_adjacent(bc, br, ec, er)) {
        if (statuses[ec][er] == 'E') {
            statuses[ec][er] = statuses[bc][br];
            statuses[bc][br] = 'E';
            return true;
        }
    } else {
        std::vector<rowcol> visited;
        std::vector<rowcol> to_visit;
        to_visit.push_back({bc,br});
        while (!to_visit.empty()) {
            rowcol curr = to_visit[0];
            to_visit.erase(to_visit.begin());
            visited.push_back(curr);
            for (int adj = 0; adj < 6; adj++) {
                rowcol curradj = adjacents[curr.col][curr.row][adj];
                if (statuses[curradj.col][curradj.row] == 'R' || statuses[curradj.col][curradj.row] == 'B') {
                    for (int adjadj = 0; adjadj < 6; adjadj++) {
                        rowcol curradjadj = adjacents[curradj.col][curradj.row][adjadj];
                        if (is_empty_opposite(curr.col, curr.row, curradjadj.col, curradjadj.row)) {
                            rowcol empty_oppo = {curradjadj.col, curradjadj.row};
                            if (empty_oppo.row == er && empty_oppo.col == ec) {
                                statuses[empty_oppo.row][empty_oppo.col] = statuses[bc][br];
                                statuses[bc][br] = 'E';
                                return true;
                            }
                            if (!std::count(visited.begin(), visited.end(), empty_oppo) && !std::count(to_visit.begin(), to_visit.end(), empty_oppo)) {
                                to_visit.push_back(empty_oppo);
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void gameboard::init_board() {
    set_tiles();
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 17; j++) {
            set_adjacents(i, j);
        }
    }
}


char gameboard::victory_satisfied() {
    bool redWin = true;
    bool blueWin = true;
    for (rowcol r : top_pos) {
        if (statuses[r.col][r.row] != 'B') {
            blueWin = false;
            break;
        }
    }
    for (rowcol r : bot_pos) {
        if (statuses[r.col][r.row] != 'R') {
            redWin = false;
            break;
        }
    }
    if (redWin) {
        return 'R';
    }
    if (blueWin) {
        return 'B';
    }
    return 'N';
}
// if player has too many pieces leftover, return true
bool gameboard::leftover_pieces(int round, char player) {
    int count = 0;
    if (player == 'R') {
        for (rowcol r : top_pos) {
            if (statuses[r.col][r.row] == 'R') {
                count++;
            }
        }
    } else {
        for (rowcol r : bot_pos) {
            if (statuses[r.col][r.row] == 'B') {
                count++;
            }
        }
    }
    if (round == 20) {
        if (count > 5) {
            return true;
        }
    }
    if (round == 25) {
        if (count > 2) {
            return true;
        }
    }
    if (round == 30) {
        if (count > 0) {
            return true;
        }
    }
    return false;
}
