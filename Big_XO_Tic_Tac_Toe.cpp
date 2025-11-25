#include <iostream>
#include <iomanip>
#include "Big_XO_Tic_Tac_Toe.h"

using namespace std;

// ---------------- Big_XO_Board ----------------

X_O_Board::X_O_Board() : Board(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool X_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
	//just 24 moves possible
    if (n_moves >= 24) {
        return false;
    }

}

//count sequences of 3 same symbols in a row/column/diagonal
int X_O_Board::count_sequences(char sym) {
    int count = 0;

    // Rows
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c <= 2; c++) {
            if (board[r][c] == sym &&
                board[r][c + 1] == sym &&
                board[r][c + 2] == sym)
                count++;
        }
    }

    // Columns
    for (int c = 0; c < 5; c++) {
        for (int r = 0; r <= 2; r++) {
            if (board[r][c] == sym &&
                board[r + 1][c] == sym &&
                board[r + 2][c] == sym)
                count++;
        }
    }

    // Main Diagonal 
    for (int r = 0; r <= 2; r++) {
        for (int c = 0; c <= 2; c++) {
            if (board[r][c] == sym &&
                board[r + 1][c + 1] == sym &&
                board[r + 2][c + 2] == sym)
                count++;
        }
    }

    // Anti diagonal 
    for (int r = 2; r < 5; r++) {
        for (int c = 0; c <= 2; c++) {
            if (board[r][c] == sym &&
                board[r - 1][c + 1] == sym &&
                board[r - 2][c + 2] == sym)
                count++;
        }
    }

    return count;
}

bool X_O_Board::is_win(Player<char>* player) {

    if (n_moves < 24)
        return false;

    int xSeq = count_sequences('X');
    int oSeq = count_sequences('O');

    char sym = player->get_symbol();

    if (sym == 'X' && xSeq > oSeq) return true;
    if (sym == 'O' && oSeq > xSeq) return true;

    return false;
}

bool X_O_Board::is_draw(Player<char>* player) {

    if (n_moves < 24)
        return false;

    int xSeq = count_sequences('X');
    int oSeq = count_sequences('O');

    return xSeq == oSeq;
}

bool X_O_Board::game_is_over(Player<char>* player) {
    return n_moves >= 24;   
}

// ---------------- Big_XO_UI ----------------

XO_UI::XO_UI() : UI<char>("Welcome to 5 x 5 Tic Tac Toe X-O Game", 3) {}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type) {

    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_UI::get_move(Player<char>* player) {

    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name()
            << " (" << player->get_symbol()
            << ") enter your move x y (0 to 4): ";
        cin >> x >> y;
    }
    else {
       
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }

    return new Move<char>(x, y, player->get_symbol());
}
