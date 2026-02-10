//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Obstacles_Tic_Tac_Toe.h"
using namespace std;

//--------------------------------------- Obstacles_XO_Board Implementation

Obstacles_XO_Board::Obstacles_XO_Board() : Board(6, 6) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}
bool Obstacles_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    char obstacles = '#';

    int obs1_x = rand() % get_rows();
    int obs1_y = rand() % get_columns();
    int obs2_x = rand() % get_rows();
    int obs2_y = rand() % get_columns();
    
    bool obs1_valid = false; // Check the validation of the first obstacle move
    bool obs2_valid = false; // Check the validation of the second obstacle move

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
        if (board[obs1_x][obs1_y] != blank_symbol) obs1_valid = true; // Validate the first obstacle random move
        while (obs1_valid) { // Loop until the move is valid
            obs1_x = rand() % get_rows();
            obs1_y = rand() % get_columns();
            if (board[obs1_x][obs1_y] == blank_symbol) obs1_valid = false;
            continue;
        }
        if (board[obs2_x][obs2_y] != blank_symbol) obs2_valid = true; // Validate the second obstacle random move
        while (obs2_valid) {
            obs2_x = rand() % get_rows();
            obs2_y = rand() % get_columns();
            if (board[obs2_x][obs2_y] == blank_symbol) obs2_valid = false;
            continue;
        }
        if (mark == 'O') { // Apply the 2 obstacles after every round (one turn for each player)

            n_moves++;
            board[obs1_x][obs1_y] = obstacles; // Apply the first obstacle move

            n_moves++;
            board[obs2_x][obs2_y] = obstacles; // Apply the second obstacle move
            
        }
        return true;
    }
    return false;
}
bool Obstacles_XO_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c, char d) {
        return a == b && b == c && c == d && a != blank_symbol && a != obstacles;
        };

    // Check rows
    for (int i = 5; i >= 0; --i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2], board[i][3]) && board[i][0] == sym) ||
            (all_equal(board[i][1], board[i][2], board[i][3], board[i][4]) && board[i][1] == sym) ||
            (all_equal(board[i][2], board[i][3], board[i][4], board[i][5]) && board[i][2] == sym))
            return true;
    }
    // Check columns
    for (int i = 0; i < 6; ++i) {
        if ((all_equal(board[0][i], board[1][i], board[2][i], board[3][i]) && board[0][i] == sym) ||
            (all_equal(board[1][i], board[2][i], board[3][i], board[4][i]) && board[1][i] == sym) ||
            (all_equal(board[2][i], board[3][i], board[4][i], board[5][i]) && board[2][i] == sym))
            return true;
    }

    // Check Main diagonal 
    for (int i = 3; i < 6; ++i) {      // Row
        for (int j = 0; j < 3; ++j) {  // Column
            if (all_equal(board[i][j], board[i - 1][j + 1], board[i - 2][j + 2], board[i - 3][j + 3]) && board[i][j] == sym)
                return true;
        }
    }

    // Check Anti diagonal 
    for (int i = 3; i < 6; ++i) {      // Row
        for (int j = 3; j < 6; ++j) {  // Column
            if (all_equal(board[i][j], board[i - 1][j - 1], board[i - 2][j - 2], board[i - 3][j - 3]) && board[i][j] == sym)
                return true;
        }
    }

    return false;
}
bool Obstacles_XO_Board::is_draw(Player<char>* p)
{
    // Board is full and no winner
    if (!is_win(p)) {
        for (auto& row : board)
            for (char cell : row)
                if (cell == blank_symbol)
                    return false;
        return true;
    }
    return false;
}

bool Obstacles_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- Obstacles_XO_UI Implementation

Obstacles_XO_UI::Obstacles_XO_UI() : UI<char>("==== Obstacles Tic-Tac-Toe Game ====", 3) {}

Player<char>* Obstacles_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_XO_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 5): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
