/**
 * @file DiamondTic_Tac_Toe.cpp
 * @brief Implementation of Diamond Tic-Tac-Toe classes.
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 */

#include "Diamond_Tic_Tac_Toe.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath> // For abs()

using namespace std;

//--------------------------------------- Diamond_X_O_Board Implementation

/**
 * @brief Constructs a Diamond_X_O_Board with 7x7 dimensions and diamond shape.
 */
Diamond_X_O_Board::Diamond_X_O_Board() : Board(7, 7) {
    // Initialize pointers to prevent garbage access
    computer_player = nullptr;
    human_player = nullptr;
    // Center is at (3, 3). Valid positions are where Manhattan distance <= 3
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (abs(i - 3) + abs(j - 3) <= 3) {
                board[i][j] = blank_symbol;
            }
            else {
                board[i][j] = '#';
            }
        }
    }
}

/**
 * @brief Updates the board with a move.
 */
bool Diamond_X_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

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

/**
 * @brief Checks if player has won according to diamond game rules.
 */
bool Diamond_X_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    vector<pair<int, int>> directions = {
        {0, 1},   // Horizontal
        {1, 0},   // Vertical
        {1, 1},   // Diagonal ↘
        {1, -1}   // Diagonal ↙
    };

    vector<bool> found_three(4, false);
    vector<bool> found_four(4, false);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!is_valid_position(i, j) || board[i][j] != sym)
                continue;

            for (int dir_idx = 0; dir_idx < 4; ++dir_idx) {
                auto& dir = directions[dir_idx];
                int dx = dir.first, dy = dir.second;

                // Check 3 in line
                bool valid_three = true;
                for (int k = 0; k < 3; ++k) {
                    int ni = i + k*dx, nj = j + k*dy;
                    if (!is_valid_position(ni, nj) || board[ni][nj] != sym) {
                        valid_three = false;
                        break;
                    }
                }
                if (valid_three) found_three[dir_idx] = true;

                // Check 4 in line
                bool valid_four = true;
                for (int k = 0; k < 4; ++k) {
                    int ni = i + k*dx, nj = j + k*dy;
                    if (!is_valid_position(ni, nj) || board[ni][nj] != sym) {
                        valid_four = false;
                        break;
                    }
                }
                if (valid_four) found_four[dir_idx] = true;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i != j && found_three[i] && found_four[j]) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Checks if player has lost.
 */
bool Diamond_X_O_Board::is_lose(Player<char>* player) {
    if (computer_player == nullptr || human_player == nullptr) {
        return false;
    }


    if (player == computer_player) return is_win(human_player);
    else return is_win(computer_player);
}

/**
 * @brief Checks if game is a draw.
 */
bool Diamond_X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 25 && !is_win(player));
}

/**
 * @brief Checks if game is over.
 */
bool Diamond_X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Checks if current state is terminal.
 */
bool Diamond_X_O_Board::is_terminal() {
    return is_win(computer_player) || is_win(human_player) || n_moves == 25;
}

/**
 * @brief Sets player pointers.
 */
void Diamond_X_O_Board::set_players(Player<char>* comp, Player<char>* human) {
    computer_player = comp;
    human_player = human;
}

/**
 * @brief Gets valid positions.
 */
vector<pair<int, int>> Diamond_X_O_Board::get_valid_positions() {
    vector<pair<int, int>> positions;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == blank_symbol) {
                positions.push_back({i, j});
            }
        }
    }
    return positions;
}

/**
 * @brief Counts lines of specific length.
 */
int Diamond_X_O_Board::count_lines(Player<char>* player, int length) {
    const char sym = player->get_symbol();
    int count = 0;
    vector<pair<int, int>> directions = {{0,1}, {1,0}, {1,1}, {1,-1}};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!is_valid_position(i, j) || board[i][j] != sym) continue;

            for (auto& dir : directions) {
                int dx = dir.first, dy = dir.second;
                bool valid_line = true;
                for (int k = 0; k < length; ++k) {
                    int ni = i + k*dx, nj = j + k*dy;
                    if (!is_valid_position(ni, nj) || board[ni][nj] != sym) {
                        valid_line = false;
                        break;
                    }
                }
                if (valid_line) count++;
            }
        }
    }
    return count;
}

/**
 * @brief Evaluates the board state.
 */
int Diamond_X_O_Board::evaluate() {
    if(is_win(computer_player)) return 100;
    if(is_win(human_player)) return -100;

    int score = 0;
    score += count_lines(computer_player, 2) * 5;
    score -= count_lines(human_player, 2) * 5;
    score += count_lines(computer_player, 3) * 20;
    score -= count_lines(human_player, 3) * 20;

    // Center control (3,3 is the new center)
    if (board[3][3] == computer_player->get_symbol()) score += 10;

    return score;
}

/**
 * @brief Finds the best move using minimax.
 */
Move<char>* Diamond_X_O_Board::find_best_move() {
    int best_score = -1000;
    Move<char>* best_move = nullptr;
    vector<pair<int, int>> valid_positions = get_valid_positions();
    int search_depth = 5;

    for (auto& pos : valid_positions) {
        int i = pos.first, j = pos.second;
        board[i][j] = computer_player->get_symbol();
        n_moves++;

        int score = minimax(false, -1000, 1000, search_depth);

        board[i][j] = blank_symbol;
        n_moves--;

        if (score > best_score) {
            best_score = score;
            best_move = new Move<char>(i, j, computer_player->get_symbol());
        }
    }

    if (best_move == nullptr && !valid_positions.empty()) {
        auto& first = valid_positions[0];
        best_move = new Move<char>(first.first, first.second, computer_player->get_symbol());
    }
    return best_move;
}

/**
 * @brief Minimax algorithm.
 */
int Diamond_X_O_Board::minimax(bool is_maximizing, int alpha, int beta, int depth) {
    if (is_terminal() || depth == 0) return evaluate();

    vector<pair<int, int>> valid_positions = get_valid_positions();

    if (is_maximizing) {
        int max_eval = -1000;
        for (auto& pos : valid_positions) {
            int i = pos.first, j = pos.second;
            board[i][j] = computer_player->get_symbol();
            n_moves++;
            int eval = minimax(false, alpha, beta, depth - 1);
            board[i][j] = blank_symbol;
            n_moves--;
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return max_eval;
    }
    else {
        int min_eval = 1000;
        for (auto& pos : valid_positions) {
            int i = pos.first, j = pos.second;
            board[i][j] = human_player->get_symbol();
            n_moves++;
            int eval = minimax(true, alpha, beta, depth - 1);
            board[i][j] = blank_symbol;
            n_moves--;
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return min_eval;
    }
}

/**
 * @brief Checks if position is valid.
 */
bool Diamond_X_O_Board::is_valid_position(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
    return (board[x][y] != '#');
}

//--------------------------------------- Diamond_X_O_UI Implementation

Diamond_X_O_UI::Diamond_X_O_UI() : UI<char>("Welcome to FCAI Diamond X-O Game ", 3) {
    player1 = nullptr;
    player2 = nullptr;
}

Player<char>* Diamond_X_O_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_X_O_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 6): ";
        int x, y;
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        // [TWEAK 1]: Use static_cast instead of dynamic_cast
        // static_cast is faster and safer here since we know the type for sure.
        Diamond_X_O_Board* board = static_cast<Diamond_X_O_Board*>(player->get_board_ptr());

        // [TWEAK 2]: Crash Prevention Check
        if (board == nullptr) {
            cout << "\nFATAL ERROR: Computer player has no board! (pointer is null)\n";
            exit(1);
        }

        Player<char>* computer = player;
        Player<char>* human = nullptr;

        // [TWEAK 3]: Robust Opponent Detection
        // This ensures we always find the 'other' player, even if pointers don't match exactly.
        if (player1 != nullptr && player2 != nullptr) {
            if (player->get_symbol() == player1->get_symbol()) {
                human = player2; // If I am P1, opponent is P2
            } else {
                human = player1; // If I am P2, opponent is P1
            }
        }

        // [TWEAK 4]: Ensure pointers are valid before setting
        if (human == nullptr) {
            cout << "\nFATAL ERROR: Could not determine human opponent!\n";
            exit(1);
        }

        board->set_players(computer, human);
        return board->find_best_move();
    }
}

/**
 * @brief Displays the diamond-shaped board matrix.
 */
void Diamond_X_O_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    // 1. Column Headers (0 to 6)
    cout << "\n   ";
    for (int j = 0; j < 7; ++j) cout << "   " << j;
    cout << "\n";

    // 2. Rows 0 to 6
    for (int r = 0; r < 7; ++r) {
        // Calculate the valid columns for current row to know indentation
        int current_start = abs(3 - r);
        int current_end = 6 - abs(3 - r);

        // --- Draw Upper Border ---
        cout << "    "; // Margin

        if (r == 0) {
            // Special tip for the very top row
            cout << string(3 * 4 + 1, ' ') << "-+-\n";
        }
        else {
            // Calculate the width of the separator between r-1 and r
            // It covers the union of columns of both rows
            int prev_start = abs(3 - (r - 1));
            int prev_end = 6 - abs(3 - (r - 1));

            int border_start = min(current_start, prev_start);
            int border_end = max(current_end, prev_end);

            // Indentation
            cout << string(border_start * 4, ' ');

            // Draw lines
            for (int k = border_start; k <= border_end; ++k) {
                cout << "+---";
            }
            cout << "+\n";
        }

        // --- Draw Cell Content ---
        cout << setw(2) << r << "  "; // Row Index
        cout << string(current_start * 4, ' '); // Indentation

        for (int k = current_start; k <= current_end; ++k) {
            char mark = matrix[r][k];
            if (mark == '#' || mark == 0) mark = ' ';
            cout << "| " << mark << " ";
        }
        cout << "|\n";
    }

    // 3. Special Bottom Tip (For Row 6)
    cout << "    " << string(3 * 4 + 1, ' ') << "-+-\n" << endl;
}

Player<char> **Diamond_X_O_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);
    player1 = players[0];

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);
    player2 = players[1];

    return players;
}