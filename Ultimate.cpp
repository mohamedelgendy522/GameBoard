#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <bits/stdc++.h>
#include "Ultimate.h"
using namespace std;

/**
 * @brief Matrix representing the status of each 3×3 sub-board in Ultimate X-O.
 *
 * Values:
 *  - '.' → sub-board not decided yet
 *  - 'X' or 'O' → sub-board winner
 */

vector<vector<char>> Matrix(3, vector<char>(3, '.'));

/**
 * @brief Constructor for Ultimate board.
 *
 * Initializes a 9×9 board and fills all cells with the blank symbol.
 */


Ultimate::Ultimate() : Board(9, 9) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}
int steps = 0 ;
int row , col;


/**
 * @brief Updates the Ultimate X-O board with a given move.
 *
 * Validates if the targeted sub-board is still open.
 * If the move is allowed, it applies or removes the symbol (undo).
 *
 * @param move Pointer to Move<char> containing position + symbol.
 * @return true if the move was successfully applied, false otherwise.
 */



bool Ultimate::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    if ((x>=0 && x<=2) && (y>=0 && y<=2) && Matrix[0][0] != '.') return false;
    if ((x>=0 && x<=2) && (y>=3 && y<=5) && Matrix[0][1] != '.') return false;
    if ((x>=0 && x<=2) && (y>=6 && y<=8) && Matrix[0][2] != '.') return false;

    if ((x>=3 && x<=5) && (y>=0 && y<=2) && Matrix[1][0] != '.') return false;
    if ((x>=3 && x<=5) && (y>=3 && y<=5) && Matrix[1][1] != '.') return false;
    if ((x>=3 && x<=5) && (y>=6 && y<=8) && Matrix[1][2] != '.') return false;

    if ((x>=6 && x<=8) && (y>=0 && y<=2) && Matrix[2][0] != '.') return false;
    if ((x>=6 && x<=8) && (y>=3 && y<=5) && Matrix[2][1] != '.') return false;
    if ((x>=6 && x<=8) && (y>=6 && y<=8) && Matrix[2][2] != '.') return false;

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            board[x][y] = toupper(mark);
        }
        return true;
        }
    return false;
}


/**
 * @brief Checks if the player won either the small sub-board or the whole Ultimate game.
 *
 * Steps:
 *  1. Identify which 3×3 sub-board the last move belongs to.
 *  2. Check if the player won that sub-board.
 *  3. Update Matrix[][] if sub-board is won or drawn.
 *  4. Check if Matrix[][] has a 3-in-a-row → Ultimate victory.
 *
 * @param player Pointer to the player whose win is being checked.
 * @return true if the player has won the entire Ultimate game.
 */

bool Ultimate::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
     };


    // ------- All sub-board checks remain unchanged -------
    // (The logic is correct — only comments needed; not editing logic)

    // ---- SUB-BOARD CHECKS ↓ ----
    // Every block sets Matrix[i][j] if the player wins that sub-board.
    // If the board fills completely → mark sub-board as finished (step counter++)


    if ((row>=0 && row<=2) && (col>=0 && col<=2)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
                (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym) ||
                (all_equal(board[0][0], board[1][1], board[2][2]) && board[0][0] == sym) ||
                (all_equal(board[0][2], board[1][1], board[2][0]) && board[0][2] == sym))
            {
                if (Matrix[0][0] == '.') {
                    Matrix[0][0] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 3 ; ++i) {
            for (int j = 0; j < 3 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[0][0] == '.') {
            steps++;
        }
    }

// (0,1)
    if ((row>=0 && row<=2) && (col>=3 && col<=5)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[i][3], board[i][4], board[i][5]) && board[i][3] == sym) ||
                (all_equal(board[0][3+i], board[1][3+i], board[2][3+i]) && board[0][3+i] == sym) ||
                (all_equal(board[0][3], board[1][4], board[2][5]) && board[0][3] == sym) ||
                (all_equal(board[0][5], board[1][4], board[2][3]) && board[0][5] == sym))
            {
                if (Matrix[0][1] == '.') {
                    Matrix[0][1] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 3 ; ++i) {
            for (int j = 3; j < 6 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[0][1] == '.') {
            steps++;
        }
    }

// (0,2)
    if ((row>=0 && row<=2) && (col>=6 && col<=8)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[i][6], board[i][7], board[i][8]) && board[i][6] == sym) ||
                (all_equal(board[0][6+i], board[1][6+i], board[2][6+i]) && board[0][6 + i] == sym) ||
                (all_equal(board[0][6], board[1][7], board[2][8]) && board[0][6] == sym) ||
                (all_equal(board[0][8], board[1][7], board[2][6]) && board[0][8] == sym))
            {
                if (Matrix[0][2] == '.') {
                    Matrix[0][2] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 3 ; ++i) {
            for (int j = 6; j < 9 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[0][2]=='.') {
            steps++;
        }
    }

// (1,0)
    if ((row>=3 && row<=5) && (col>=0 && col<=2)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[3+i][0], board[3+i][1], board[3+i][2]) && board[3+i][0] == sym) ||
                (all_equal(board[3][i], board[4][i], board[5][i]) && board[3][i] == sym) ||
                (all_equal(board[3][0], board[4][1], board[5][2]) && board[3][0] == sym) ||
                (all_equal(board[3][2], board[4][1], board[5][0]) && board[3][2] == sym))
            {
                if (Matrix[1][0] == '.') {
                    Matrix[1][0] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 3 ; i < 6 ; ++i) {
            for (int j = 0; j < 3 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[1][0] == '.') {
            steps++;
        }
    }

// (1,1)
    if ((row>=3 && row<=5) && (col>=3 && col<=5)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[3+i][3], board[3+i][4], board[3+i][5]) && board[3+i][3] == sym) ||
                (all_equal(board[3][3+i], board[4][3+i], board[5][3+i]) && board[3][3+i] == sym) ||
                (all_equal(board[3][3], board[4][4], board[5][5]) && board[3][3] == sym) ||
                (all_equal(board[3][5], board[4][4], board[5][3]) && board[3][5] == sym))
            {
                if (Matrix[1][1] == '.') {
                    Matrix[1][1] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 3 ; i < 6 ; ++i) {
            for (int j = 3 ; j < 6 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[1][1]=='.') {
            steps++;
        }
    }
// (1,2)
    if ((row>=3 && row<=5) && (col>=6 && col<=8)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[3+i][6], board[3+i][7], board[3+i][8]) && board[3+i][6] == sym) ||
                (all_equal(board[3][6+i], board[4][6+i], board[5][6+i]) && board[3][6+i] == sym) ||
                (all_equal(board[3][6], board[4][7], board[5][8]) && board[3][6] == sym) ||
                (all_equal(board[3][8], board[4][7], board[5][6]) && board[3][8] == sym))
            {
                if (Matrix[1][2] == '.') {
                    Matrix[1][2] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 3; i < 6 ; ++i) {
            for (int j = 6; j < 9 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[1][2] == '.') {
            steps++;
        }
    }

// (2,0)
    if ((row>=6 && row<=8) && (col>=0 && col<=2)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[6+i][0], board[6+i][1], board[6+i][2]) && board[6+i][0] == sym) ||
                (all_equal(board[6][i], board[7][i], board[8][i]) && board[6][i] == sym) ||
                (all_equal(board[6][0], board[7][1], board[8][2]) && board[6][0] == sym) ||
                (all_equal(board[6][2], board[7][1], board[8][0]) && board[6][2] == sym))
            {
                if (Matrix[2][0] == '.') {
                    Matrix[2][0] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 6 ; i < 9 ; ++i) {
            for (int j = 0; j < 3 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[2][0] == '.') {
            steps++;
        }
    }

// (2,1)
    if ((row>=6 && row<=8) && (col>=3 && col<=5)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[6+i][3], board[6+i][4], board[6+i][5]) && board[6+i][3] == sym) ||
                (all_equal(board[6][3+i], board[7][3+i], board[8][3+i]) && board[6][3+i] == sym) ||
                (all_equal(board[6][3], board[7][4], board[8][5]) && board[6][3] == sym) ||
                (all_equal(board[6][5], board[7][4], board[8][3]) && board[6][5] == sym))
            {
                if (Matrix[2][1] == '.') {
                    Matrix[2][1] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 6; i < 9 ; ++i) {
            for (int j = 3 ; j < 6 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[2][1] == '.') {
            steps++;
        }
    }

// (2,2)
    if ((row>=6 && row<=8) && (col>=6 && col<=8)) {
        for (int i = 0; i < 3 ; ++i) {
            if ((all_equal(board[6+i][6], board[6+i][7], board[6+i][8]) && board[6+i][6] == sym) ||
                (all_equal(board[6][6+i], board[7][6+i], board[8][6+i]) && board[6][6+i] == sym) ||
                (all_equal(board[6][6], board[7][7], board[8][8]) && board[6][6] == sym) ||
                (all_equal(board[6][8], board[7][7], board[8][6]) && board[6][8] == sym))
            {
                if (Matrix[2][2] == '.') {
                    Matrix[2][2] = sym;
                    steps++;
                }
            }
        }
        int cnt = 0;
        for (int i = 6; i < 9 ; ++i) {
            for (int j = 6 ; j < 9 ; ++j) {
                if (board[i][j] != blank_symbol) {
                    cnt++;
                }
            }
        }
        if (cnt == 9 && Matrix[2][2] == '.') {
            steps++;
        }
    }
    // ---- CHECK IF PLAYER WON THE BIG 3×3 (Ultimate) BOARD ----
    for (int i = 0; i < 3 ; ++i) {
        if ((all_equal(Matrix[i][0], Matrix[i][1], Matrix[i][2]) && Matrix[i][0] == sym) ||
            (all_equal(Matrix[0][i], Matrix[1][i], Matrix[2][i]) && Matrix[0][i] == sym) ||
            (all_equal(Matrix[0][0], Matrix[1][1], Matrix[2][2]) && Matrix[0][0] == sym) ||
            (all_equal(Matrix[0][2], Matrix[1][1], Matrix[2][0]) && Matrix[0][2] == sym))
        {
            return true; // Player won the Ultimate game
        }
    }
    return false;
}

/**
 * @brief Checks if the Ultimate game ended in a draw.
 *
 * A draw occurs when all 9 sub-boards are decided (all steps used)
 * and no player has won.
 */
bool Ultimate::is_draw(Player<char>* player) {
    return (steps == 9 && !is_win(player));
}

/**
 * @brief Determines whether the game has finished (win or draw).
 */
bool Ultimate::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/* ======================= UI SECTION ======================= */

/**
 * @brief Constructor for Ultimate_UI.
 *
 * Displays a welcome message and initializes UI with board size 3.
 */


Ultimate_UI::Ultimate_UI() : UI<char>("Weclome to FCAI Ultimate Game", 3) {}

/**
 * @brief Creates a human or computer player for Ultimate X-O.
 */

Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Ultimate_UI::~Ultimate_UI() {}

/**
 * @brief Reads or generates a move depending on player type.
 *
 * Human: user enters x y
 * Computer: random valid coordinates
 */

Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 8): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    row = x;
    col = y;
    return new Move<char>(x, y, player->get_symbol());
}
