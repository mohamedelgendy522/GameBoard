//--------------------------------------- IMPLEMENTATION

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
    // Rows
    for (int i = 5; i >=0; --i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2], board[i][3] ) && board[i][0] == sym) ||
            (all_equal(board[i][1], board[i][2], board[i][3], board[i][4] ) && board[i][1] == sym) ||
            (all_equal(board[i][2], board[i][3], board[i][4], board[i][5]) && board[i][2] == sym) ||
            (all_equal(board[i][3], board[i][4], board[i][5], board[i][6]) && board[i][3] == sym))
            return true;
    }
    // Columns
    for (int i = 0; i < 7; ++i) {
        if ((all_equal(board[0][i], board[1][i], board[2][i], board[3][i]) && board[0][i] == sym) ||
            (all_equal(board[1][i], board[2][i], board[3][i], board[4][i]) && board[1][i] == sym) ||
            (all_equal(board[2][i], board[3][i], board[4][i], board[5][i]) && board[2][i] == sym))
            return true;
    }
  
    // Main diagonal 
    for (int i = 3; i < 6; ++i) {      // Row
        for (int j = 0; j < 4; ++j) {  // Column
            if (all_equal(board[i][j], board[i - 1][j + 1], board[i - 2][j + 2], board[i - 3][j + 3]) && board[i][j] == sym)
                return true;
        }
    }

    // Anti diagonal 
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

FourInRow_UI::FourInRow_UI() : UI<char>("==== Four-In-A-Row Game ====", 3) {}

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
    auto board = b->get_board_matrix(); // get copy of the original matrix
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
            if (board[i][y] == blank_symbol) {
                x = i;
                break;
            }
        }

    }
    else if (player->get_type() == PlayerType::COMPUTER) {

        char me = player->get_symbol();
        char opp = (me == 'X' ? 'O' : 'X');
        int R = 6; // Rows
        int C = 7; // Columns

        int row, col; // For the loops

        // PRIORITY 1 — Win immediately

        for (col = 0; col < C; col++) {
            row = get_bottom_most_cell(board, col);
            if (row == -1) continue;

            board[row][col] = me; // Temporary move
            if (is_winning(board, me))
                return new Move<char>(row, col, me);
            board[row][col] = blank_symbol; // Undo
        }
        // PRIORITY 2 — Block opponent’s winning move

        for (col = 0; col < C; col++) {
            row = get_bottom_most_cell(board, col);
            if (row == -1) continue;

            board[row][col] = opp;
            if (is_winning(board, opp))
                return new Move<char>(row, col, me);
            board[row][col] = blank_symbol;
        }
        // PRIORITY 3 — Create a threat (3-in-a-row)

        for (col = 0; col < C; col++) {
            row = get_bottom_most_cell(board, col);
            if (row == -1) continue;

            board[row][col] = me;
            if (create_threat(board, me)) {
                board[row][col] = blank_symbol;
                return new Move<char>(row, col, me);
            }
            board[row][col] = blank_symbol;
        }
        // PRIORITY 4 — Block opponent's threat

        if (create_threat(board, opp)) {
            // Find all columns that block the threat
            vector<int> blocking_columns;
            for (col = 0; col < C; col++) {
                row = get_bottom_most_cell(board, col);
                if (row == -1) continue;

                board[row][col] = me;
                if (!create_threat(board, opp)) {
                    blocking_columns.push_back(col);
                }
                board[row][col] = blank_symbol;
            }

            // If there blocking moves found
            if (!blocking_columns.empty()) {
                // Sort blocking columns and prefer rightmost to avoid giving opponent setup
                int best_col = blocking_columns[0];
                for (int bc : blocking_columns) {
                    if (bc > best_col) best_col = bc;
                }
                row = get_bottom_most_cell(board, best_col);
                return new Move<char>(row, best_col, me);
            }
        }
        // PRIORITY 5 — Block opponent's 2-in-a-row

        for (col = 0; col < C; col++) {
            row = get_bottom_most_cell(board, col);
            if (row == -1) continue;

            board[row][col] = me;
            if (two_in_row(board, row, col, opp)) {
                board[row][col] = blank_symbol;
                return new Move<char>(row, col, me);
            }
            board[row][col] = blank_symbol;
        }
        // PRIORITY 6 — Prefer center columns

        vector<int> center_preference = { 3, 2, 4, 1, 5, 0, 6 };
        for (int col : center_preference) {
            row = get_bottom_most_cell(board, col);
            if (row != -1) {
                return new Move<char>(row, col, me);
            }
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}
bool is_winning(const vector<vector<char>>& b, char sym) {
    int R = 6;
    int C = 7;

    // Horizontal
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C - 3; j++)
            if (b[i][j] == sym && b[i][j + 1] == sym &&
                b[i][j + 2] == sym && b[i][j + 3] == sym)
                return true;

    // Vertical
    for (int i = 0; i < R - 3; i++)
        for (int j = 0; j < C; j++)
            if (b[i][j] == sym && b[i + 1][j] == sym &&
                b[i + 2][j] == sym && b[i + 3][j] == sym)
                return true;

    // Main diagonal
    for (int i = 0; i < R - 3; i++)
        for (int j = 0; j < C - 3; j++)
            if (b[i][j] == sym && b[i + 1][j + 1] == sym &&
                b[i + 2][j + 2] == sym && b[i + 3][j + 3] == sym)
                return true;

    // Anti diagonal
    for (int i = 0; i < R - 3; i++)
        for (int j = 3; j < C; j++)
            if (b[i][j] == sym && b[i + 1][j - 1] == sym &&
                b[i + 2][j - 2] == sym && b[i + 3][j - 3] == sym)
                return true;

    return false;
}

bool create_threat(const vector<vector<char>>& b, char sym) {
    char blank_symbol = '.';

    int R = 6;
    int C = 7;

    auto gravity_ok = [&](int r, int c) {
        return (r == R - 1 || b[r + 1][c] != blank_symbol);
        };

    // Horizontal
    for (int r = 0; r < R; r++) {
        for (int c = 0; c <= C - 4; c++) {
            int count_sym = 0;
            int empty_r = -1, empty_c = -1;
            for (int k = 0; k < 4; k++) {
                if (b[r][c + k] == sym) count_sym++;
                else if (b[r][c + k] == blank_symbol) empty_r = r, empty_c = c + k;
            }
            if (count_sym == 3 && empty_r != -1 && gravity_ok(empty_r, empty_c)) return true;
        }
    }

    // Vertical
    for (int r = 0; r <= R - 4; r++) {
        for (int c = 0; c < C; c++) {
            int count_sym = 0;
            int empty_r = -1, empty_c = -1;
            for (int k = 0; k < 4; k++) {
                if (b[r + k][c] == sym) count_sym++;
                else if (b[r + k][c] == blank_symbol) empty_r = r + k, empty_c = c;
            }
            if (count_sym == 3 && empty_r != -1 && gravity_ok(empty_r, empty_c)) return true;
        }
    }

    // Main diagonal
    for (int r = 0; r <= R - 4; r++) {
        for (int c = 0; c <= C - 4; c++) {
            int count_sym = 0;
            int empty_r = -1, empty_c = -1;
            for (int k = 0; k < 4; k++) {
                if (b[r + k][c + k] == sym) count_sym++;
                else if (b[r + k][c + k] == blank_symbol) empty_r = r + k, empty_c = c + k;
            }
            if (count_sym == 3 && empty_r != -1 && gravity_ok(empty_r, empty_c)) return true;
        }
    }

    // Anti diagonal
    for (int r = 0; r <= R - 4; r++) {
        for (int c = 3; c < C; c++) {
            int count_sym = 0;
            int empty_r = -1, empty_c = -1;
            for (int k = 0; k < 4; k++) {
                if (b[r + k][c - k] == sym) count_sym++;
                else if (b[r + k][c - k] == blank_symbol) empty_r = r + k, empty_c = c - k;
            }
            if (count_sym == 3 && empty_r != -1 && gravity_ok(empty_r, empty_c)) return true;
        }
    }

    return false;
}
bool two_in_row(const vector<vector<char>>& b, int r, int c, char opp) {
    // A defensive way to avoid giving opponent setup
    
    int R = 6, C = 7;

    // Horizontal
    int left = 0, right = 0;
    for (int j = c - 1; j >= 0 && b[r][j] == opp; j--) left++;
    for (int j = c + 1; j < C && b[r][j] == opp; j++) right++;
    if (left + right >= 2) return true;

    // Vertical
    int down = 0;
    for (int i = r + 1; i < R && b[i][c] == opp; i++) down++;
    if (down >= 2) return true;

    // Main diagonal 
    int diagonal_down = 0, diagonal_up = 0;
    for (int i = r + 1, j = c + 1; i < R && j < C && b[i][j] == opp; i++, j++) diagonal_down++;
    for (int i = r - 1, j = c - 1; i >= 0 && j >= 0 && b[i][j] == opp; i--, j--) diagonal_up++;
    if (diagonal_down + diagonal_up >= 2) return true;

    // Anti diagonal
    int anti_down = 0, anti_up = 0;
    for (int i = r + 1, j = c - 1; i < R && j >= 0 && b[i][j] == opp; i++, j--) anti_down++;
    for (int i = r - 1, j = c + 1; i >= 0 && j < C && b[i][j] == opp; i--, j++) anti_up++;
    if (anti_down + anti_up >= 2) return true;

    return false;
}

int get_bottom_most_cell(const vector<vector<char>>& b, int col) {
    for (int r = 5; r >= 0; r--)
        if (b[r][col] == '.') return r;
    return -1;
}



