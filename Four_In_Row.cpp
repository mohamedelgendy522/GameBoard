#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Four_In_Row.h"

using namespace std;

//--------------------------------------- FourInRow_Board Implementation

FourInRow_Board::FourInRow_Board() : Board(6,7) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool FourInRow_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool FourInRow_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c, char d) {
        return a == b && b == c  && c == d && a != blank_symbol;
        };

    // Check rows
    for (int i = 5; i >=0; --i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2], board[i][3] ) && board[i][0] == sym) ||
            (all_equal(board[i][1], board[i][2], board[i][3], board[i][4] ) && board[i][1] == sym) ||
            (all_equal(board[i][2], board[i][3], board[i][4], board[i][5]) && board[i][2] == sym) ||
            (all_equal(board[i][3], board[i][4], board[i][5], board[i][6]) && board[i][3] == sym))
            return true;
    }
    // Check columns
    for (int i = 0; i < 7; ++i) {
        if ((all_equal(board[0][i], board[1][i], board[2][i], board[3][i]) && board[0][i] == sym) ||
            (all_equal(board[1][i], board[2][i], board[3][i], board[4][i]) && board[1][i] == sym) ||
            (all_equal(board[2][i], board[3][i], board[4][i], board[5][i]) && board[2][i] == sym))
            return true;
    }
  
    // Check diagonal '\'
    for (int i = 3; i < 6; ++i) {      // Row
        for (int j = 0; j < 4; ++j) {  // Column
            if (all_equal(board[i][j], board[i - 1][j + 1], board[i - 2][j + 2], board[i - 3][j + 3]) && board[i][j] == sym)
                return true;
        }
    }

    // Check diagonal '/'
    for (int i = 3; i < 6; ++i) {      // Row
        for (int j = 3; j < 7; ++j) {  // Column
            if (all_equal(board[i][j], board[i - 1][j - 1], board[i - 2][j - 2], board[i - 3][j - 3]) && board[i][j] == sym)
                return true;
        }
    }

    return false;
}

bool FourInRow_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

bool FourInRow_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- FourInRow_UI Implementation

FourInRow_UI::FourInRow_UI() : UI<char>("Weclome to Four-In-A-Row Game", 3) {}

Player<char>* FourInRow_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* FourInRow_UI::get_move(Player<char>* player) {
    int x = 1;
    int y;
    Board<char>* b = player->get_board_ptr(); // get the board
    auto board_copy = b->get_board_matrix(); // get copy of the original matrix
    char blank_symbol = '.';

    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << "\nPlease enter the value of y (0 to 6): ";
            cin >> y;
            if (y > 6 || y < 0) { continue; }
            else { break; }
        }
        
        // Find the bottom-most empty cell
        for (int i = 5; i >= 0; i--) {
            if (board_copy[i][y] == blank_symbol) {
                x = i;
                break;
            }
        }
    
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = 1;
        y = rand() % player->get_board_ptr()->get_columns();
        for (int i = 5; i >= 0; i--) {
            if (board_copy[i][y] == blank_symbol) {
                x = i;
                break;
            }
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}
