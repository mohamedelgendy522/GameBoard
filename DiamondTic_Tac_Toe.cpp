#include "DiamondTic_Tac_Toe.h"

#include <iostream>
#include <iomanip>
#include <cctype>
#include "Misere_Tic_Tac_Toe.h"
using namespace std;
Diamond_X_O_Board :: Diamond_X_O_Board() : Board(10,10) {

    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            // Check if the pair (i,j) is in the required list
            if ((i == 1 && j == 4) ||
                (i == 2 && (j == 3 || j == 4 || j == 5)) ||
                (i == 3 && (j == 2 || j == 3 || j == 4 || j == 5 || j == 6)) ||
                (i == 4 && (j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6 || j == 7)) ||
                (i == 5 && (j == 2 || j == 3 || j == 4 || j == 5 || j == 6)) ||
                (i == 6 && (j == 3 || j == 4 || j == 5)) ||
                (i == 7 && j == 4)) {
                board[i][j] = blank_symbol;
            }
            else {
                board[i][j] = '#';
            }
        }
    }

}
bool Diamond_X_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (is_valid_position(x, y) && (board[x][y] == blank_symbol || mark == 0)) {
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
bool Diamond_X_O_Board::is_win(Player<char>*player) {
    const char sym = player->get_symbol();
    bool found_three = false;
    bool found_four = false;
    string three_direction, four_direction;


    vector<pair<int, int>> directions = {
        {0, 1},  // Horizontal
        {1, 0},  // virtecal
        {1, 1},  // Diagonal ↘
        {1, -1}  // Diagonal ↙
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!is_valid_position(i, j) || board[i][j] != sym) continue;

            // Check every direction
            for (auto& dir : directions) {
                int dx = dir.first, dy = dir.second;

                // Longitude check 3
                if (i + 2*dx < rows && j + 2*dy < columns && j + 2*dy >= 0) {
                    bool valid_three = true;
                    for (int k = 0; k < 3; ++k) {
                        int ni = i + k*dx, nj = j + k*dy;
                        if (!is_valid_position(ni, nj) || board[ni][nj] != sym) {
                            valid_three = false;
                            break;
                        }
                    }
                    if (valid_three) {
                        found_three = true;
                        three_direction = (dx == 0) ? "horizontal" : (dy == 0) ? "vertical" : "diagonal";
                    }
                }

                // Longitude check 4
                if (i + 3*dx < rows && j + 3*dy < columns && j + 3*dy >= 0) {
                    bool valid_four = true;
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + k*dx, nj = j + k*dy;
                        if (!is_valid_position(ni, nj) || board[ni][nj] != sym) {
                            valid_four = false;
                            break;
                        }
                    }
                    if (valid_four) {
                        found_four = true;
                        four_direction = (dx == 0) ? "horizontal" : (dy == 0) ? "vertical" : "diagonal";
                    }
                }
            }
        }
    }


    return found_three && found_four && three_direction != four_direction;
}

bool Diamond_X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 25 && !is_win(player));
}
bool Diamond_X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Diamond_X_O_UI::Diamond_X_O_UI() : UI<char>("Welcome to FCAI Diamond X-O Game ", 3) {}

Player<char>* Diamond_X_O_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
bool Diamond_X_O_Board::is_valid_position(int x, int y) {
    return ((x == 1 && y == 4) ||
            (x == 2 && (y == 3 || y == 4 || y == 5)) ||
            (x == 3 && (y == 2 || y == 3 || y == 4 || y == 5 || y == 6)) ||
            (x == 4 && (y == 1 || y == 2 || y == 3 || y == 4 || y == 5 || y == 6 || y == 7)) ||
            (x == 5 && (y == 2 || y == 3 || y == 4 || y == 5 || y == 6)) ||
            (x == 6 && (y == 3 || y == 4 || y == 5)) ||
            (x == 7 && y == 4)) &&
            board[x][y] != '#';
}

Move<char>* Diamond_X_O_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 9): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        vector<pair<int, int>> valid_moves;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (player->get_board_ptr()->get_cell(i, j) == '_') {

                    Diamond_X_O_Board* board = dynamic_cast<Diamond_X_O_Board*>(player->get_board_ptr());
                    if (board && board->is_valid_position(i, j)) {
                        valid_moves.push_back({i, j});
                    }
                }
            }
        }

        if (!valid_moves.empty()) {
            int random_index = rand() % valid_moves.size();
            x = valid_moves[random_index].first;
            y = valid_moves[random_index].second;
        } else {
            x = y = 0; // fallback
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}
void Diamond_X_O_UI::display_board_matrix(const vector<vector<char> > &matrix) const {
    if (matrix.empty() || matrix[0].empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n  ";
    for (int j = 0; j < cols; ++j)
        cout << setw(cell_width + 2) << j;
    cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width) << matrix[i][j] << " |";
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
    }
    cout << endl;
}

