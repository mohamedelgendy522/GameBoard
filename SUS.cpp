#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cstdlib>
#include "SUS.h"
using namespace std;

SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool SUS_Board::update_board(Move<char>* move) {
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
void SUS_Board::update_scores(Player<char>* player)
{
    auto get_sus = [&](char a, char b, char c) {
        return a == 'S' && b == 'U' && c == 'S';
        };

    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == 'S' && board[i][1] == blank_symbol && board[i][2] == 'S') {
            row_u[i] = true;
        }
        if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == blank_symbol) {
            row_s[i] = true;
        }
        if (board[i][0] == blank_symbol && board[i][1] == 'U' && board[i][2] == 'S') {
            row_s[i] = true;
         }
    }
        for (int i = 0; i < 3; i++) {
            if (get_sus(board[i][0], board[i][1], board[i][2])) {
                if (row_u[i] == true) {
                    score_U++;
                    row_u[i] = false;
                }
            }
        }
   
        for (int i = 0; i < 3; i++) {
            if (get_sus(board[i][0], board[i][1], board[i][2])) {
                if (row_s[i] == true) {
                    score_S++;
                    row_s[i] = false;
                }
            }
        }      
    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == 'S' && board[1][i] == blank_symbol && board[2][i] == 'S')
            column_u[i] = true;
        else if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == blank_symbol)
            column_s[i] = true;
        else if (board[0][i] == blank_symbol && board[1][i] == 'U' && board[2][i] == 'S')
            column_s[i] = true;
    }
    for (int i = 0; i < 3; i++) {
        if (get_sus(board[0][i], board[1][i], board[2][i])) {
            if (column_u[i] == true) {
                score_U++;
                column_u[i] = false;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (get_sus(board[0][i], board[1][i], board[2][i])) {
            if (column_s[i] == true) {
                score_S++;
                column_s[i] = false;
            }
        }
    }
    // Main Diagonal
    if (board[0][0] == 'S' && board[1][1] == blank_symbol && board[2][2] == 'S')
        main_diagonal_u = true;
    else if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == blank_symbol)
        main_diagonal_s = true;
    else if (board[0][0] == blank_symbol && board[1][1] == 'U' && board[2][2] == 'S')
        main_diagonal_s = true;

    if (get_sus(board[0][0], board[1][1], board[2][2])) {
        if (main_diagonal_u) {
            score_U++;
            main_diagonal_u = false;
        }
        else if (main_diagonal_s) {
            score_S++;
            main_diagonal_s = false;
        }
    }
    // Anti diagonal
    if (board[0][2] == 'S' && board[1][1] == blank_symbol && board[2][0] == 'S')
        anti_diagonal_u = true;
    else if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == blank_symbol)
        anti_diagonal_s = true;
    else if (board[0][2] == blank_symbol && board[1][1] == 'U' && board[2][0] == 'S')
        anti_diagonal_s = true;

    if (get_sus(board[0][2], board[1][1], board[2][0])) {
        if (anti_diagonal_u) {
            score_U++;
            main_diagonal_u = false;
        }
        else if (main_diagonal_s) {
            score_S++;
            main_diagonal_s = false;
        }
    }
}
bool SUS_Board::is_win(Player<char>* player) {
    update_scores(player);
    if (n_moves < 9) return false;
    if (score_S > score_U) return true;
    
    return false;
}

bool SUS_Board::is_lose(Player<char>* player) {
    update_scores(player);
    if (n_moves < 9)return false;
    if (score_U > score_S) return true;

    return false;
}


bool SUS_Board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;
    if (score_U == score_S) return true;
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player) || is_lose(player);
}

//--------------------------------------- XO_UI Implementation

SUS_UI::SUS_UI() : UI<char>("====SUS Game====", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x = 0;
    int y = 0;
    Board<char>* b = player->get_board_ptr(); // get the board
    auto board_copy = b->get_board_matrix(); // get copy of the original board matrix
    char blank_symbol = '.';

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {

        // Playing safely (Defense)

        // Rows
        for (int i = 0;i < 3;i++) {
            if (board_copy[i][0] == 'S' && board_copy[i][2] == blank_symbol) {
                x = i;
                y = 2;
            }
        }
        // Columns
        for (int i = 0;i < 3;i++) {
            if (board_copy[0][i] == 'S' && board_copy[2][i] == blank_symbol) {
                x = 2;
                y = i;
            }
        }

        // Scoring points (Attack)

        //Rows
        for (int i = 0;i < 3;i++) {
            if (board_copy[i][0] == board_copy[i][2] && board_copy[i][0] == 'S' && board_copy[i][1] == blank_symbol) {
                x = i;
                y = 1;
            }
        }
        // Columns
        for (int i = 0;i < 3;i++) {
            if (board_copy[0][i] == board_copy[2][i] && board_copy[0][i] == 'S' && board_copy[1][i] == blank_symbol) {
                x = 1;
                y = i;
            }
        }
        // Main Diagonal
        if (board_copy[0][0] == board_copy[2][2] && board_copy[0][0] == 'S' && board_copy[1][1] == blank_symbol) {
            x = 1;
            y = 1;
        }
        //Anti Diagonal
        if (board_copy[0][2] == board_copy[2][0] && board_copy[0][2] == 'S' && board_copy[1][1] == blank_symbol) {
            x = 1;
            y = 1;
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}
Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer"};

    string name_S = get_player_name("Player 1");
    PlayerType type_S = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name_S, 'S', type_S);

    string name_U = get_player_name("Player 2");
    PlayerType type_U = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name_U, 'U', type_U);

    return players;
}

