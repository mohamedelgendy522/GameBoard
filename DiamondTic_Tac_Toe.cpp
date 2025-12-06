/**
 * @file DiamondTic_Tac_Toe.cpp
 * @brief Implementation of Diamond Tic-Tac-Toe classes.
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 *
 * This file contains the implementation of:
 * - Diamond_X_O_Board class methods
 * - Diamond_X_O_UI class methods
 */

#include "DiamondTic_Tac_Toe.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

//--------------------------------------- Diamond_X_O_Board Implementation

/**
 * @brief Constructs a Diamond_X_O_Board with 10x10 dimensions and diamond shape.
 * @details Initializes a 10x10 board where only diamond-shaped positions are playable.
 *          Non-playable positions are marked with '#'.
 * @see Diamond_X_O_Board::Diamond_X_O_Board
 */
Diamond_X_O_Board::Diamond_X_O_Board() : Board(10,10) {
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

/**
 * @brief Updates the board with a move.
 * @param move Pointer to Move object containing coordinates and symbol.
 * @return true if move was valid and applied, false otherwise.
 * @see Diamond_X_O_Board::update_board
 */
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

/**
 * @brief Checks if player has won according to diamond game rules.
 * @param player Pointer to the player to check.
 * @return true if player has at least one line of 3 AND one line of 4 in different directions.
 * @see Diamond_X_O_Board::is_win
 */
bool Diamond_X_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    vector<pair<int, int>> directions = {
        {0, 1},   // Horizontal
        {1, 0},   // Vertical
        {1, 1},   // Diagonal ↘
        {1, -1}   // Diagonal ↙
    };

    vector<bool> found_three(4, false);  // For every direction
    vector<bool> found_four(4, false);   // For every direction

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!is_valid_position(i, j) || board[i][j] != sym)
                continue;

            // Check in every direction
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

    // Requirement: A line of 3 + a line of 4 in different directions
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i != j && found_three[i] && found_four[j]) {
                return true;  // Win!
            }
        }
    }

    return false;
}

/**
 * @brief Checks if player has lost (opponent has won).
 * @param player Pointer to the player to check.
 * @return true if opponent has won, false otherwise.
 * @see Diamond_X_O_Board::is_lose
 */
bool Diamond_X_O_Board::is_lose(Player<char>* player) {
    if (player == computer_player) {
        return is_win(human_player);
    } else {
        return is_win(computer_player);
    }
}

/**
 * @brief Checks if game is a draw.
 * @param player Pointer to the player (unused, for interface compatibility).
 * @return true if all 25 diamond positions are filled and no player has won.
 * @see Diamond_X_O_Board::is_draw
 */
bool Diamond_X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 25 && !is_win(player));
}

/**
 * @brief Checks if game is over.
 * @param player Pointer to the player.
 * @return true if game is won or drawn, false otherwise.
 * @see Diamond_X_O_Board::game_is_over
 */
bool Diamond_X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Checks if current state is terminal (game over).
 * @return true if game is over, false otherwise.
 * @see Diamond_X_O_Board::is_terminal
 */
bool Diamond_X_O_Board::is_terminal() {
    return is_win(computer_player) || is_win(human_player) || n_moves == 25;
}

/**
 * @brief Sets player pointers for the board.
 * @param comp Pointer to computer player.
 * @param human Pointer to human player.
 * @see Diamond_X_O_Board::set_players
 */
void Diamond_X_O_Board::set_players(Player<char>* comp, Player<char>* human) {
    computer_player = comp;
    human_player = human;
}

/**
 * @brief Gets all valid (empty) positions on the diamond board.
 * @return Vector of (x,y) coordinates for empty positions.
 * @see Diamond_X_O_Board::get_valid_positions
 */
vector<pair<int, int>> Diamond_X_O_Board::get_valid_positions() {
    vector<pair<int, int>> positions;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == blank_symbol) {
                positions.push_back({i, j});
            }
        }
    }
    return positions;
}

/**
 * @brief Counts lines of specific length for a player.
 * @param player Pointer to the player to count lines for.
 * @param length Length of line to count (2, 3, or 4).
 * @return Number of lines of specified length for the player.
 * @see Diamond_X_O_Board::count_lines
 */
int Diamond_X_O_Board::count_lines(Player<char>* player, int length) {
    const char sym = player->get_symbol();
    int count = 0;

    vector<pair<int, int>> directions = {{0,1}, {1,0}, {1,1}, {1,-1}};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!is_valid_position(i, j) || board[i][j] != sym)
                continue;

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
 * @brief Evaluates the board state for AI.
 * @return Score: +100 for computer win, -100 for human win, plus strategic points.
 * @details Strategic points: lines of 2 (+5), lines of 3 (+20), center control (+10).
 * @see Diamond_X_O_Board::evaluate
 */
int Diamond_X_O_Board::evaluate() {
    if(is_win(computer_player))
        return 100;

    if(is_win(human_player)) {
        return -100;
    }

    int score = 0;

    // Points for lines of 2
    score += count_lines(computer_player, 2) * 5;
    score -= count_lines(human_player, 2) * 5;

    // Points for lines of 3
    score += count_lines(computer_player, 3) * 20;
    score -= count_lines(human_player, 3) * 20;

    // Points for controlling the center
    if (board[4][4] == computer_player->get_symbol())
        score += 10;

    return score;
}

/**
 * @brief Finds the best move for computer using depth-limited minimax.
 * @return Pointer to best Move object, or any valid move if none found.
 * @see Diamond_X_O_Board::find_best_move
 */
Move<char>* Diamond_X_O_Board::find_best_move() {
    int best_score = -1000;
    Move<char>* best_move = nullptr;

    vector<pair<int, int>> valid_positions = get_valid_positions();

    // Limited depth to make it fast
    int search_depth = 5;  // You can increase it to 6-7 if you want it to be stronger.

    for (auto& pos : valid_positions) {
        int i = pos.first, j = pos.second;

        // Try the move
        board[i][j] = computer_player->get_symbol();
        n_moves++;

        // With limited depth
        int score = minimax(false, -1000, 1000, search_depth);

        // Undo
        board[i][j] = blank_symbol;
        n_moves--;

        if (score > best_score) {
            best_score = score;
            best_move = new Move<char>(i, j, computer_player->get_symbol());
        }
    }

    // If there is no movement, take the first available movement.
    if (best_move == nullptr && !valid_positions.empty()) {
        auto& first = valid_positions[0];
        best_move = new Move<char>(first.first, first.second, computer_player->get_symbol());
    }

    return best_move;
}

/**
 * @brief Minimax algorithm with alpha-beta pruning and depth limitation.
 * @param is_maximizing true if current player is computer, false if human.
 * @param alpha Alpha value for pruning.
 * @param beta Beta value for pruning.
 * @param depth Maximum search depth.
 * @return Best evaluation score for current board state.
 * @see Diamond_X_O_Board::minimax
 */
int Diamond_X_O_Board::minimax(bool is_maximizing, int alpha, int beta, int depth) {
    if (is_terminal() || depth == 0) {
        return evaluate();  // With strategic assessment
    }

    vector<pair<int, int>> valid_positions = get_valid_positions();

    if (is_maximizing) {  // Computer
        int max_eval = -1000;

        for (auto& pos : valid_positions) {
            int i = pos.first, j = pos.second;

            // Try the move
            board[i][j] = computer_player->get_symbol();
            n_moves++;

            int eval = minimax(false, alpha, beta, depth - 1);

            // Undo
            board[i][j] = blank_symbol;
            n_moves--;

            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);

            if (beta <= alpha) break;  // Alpha-Beta pruning
        }
        return max_eval;
    }
    else {  // Human
        int min_eval = 1000;

        for (auto& pos : valid_positions) {
            int i = pos.first, j = pos.second;

            // Try human movement
            board[i][j] = human_player->get_symbol();
            n_moves++;

            int eval = minimax(true, alpha, beta, depth - 1);

            // Undo
            board[i][j] = blank_symbol;
            n_moves--;

            min_eval = min(min_eval, eval);
            beta = min(beta, eval);

            if (beta <= alpha) break;  // Alpha-Beta pruning
        }
        return min_eval;
    }
}

/**
 * @brief Checks if a position is valid (part of the diamond).
 * @param x Row index (0-9).
 * @param y Column index (0-9).
 * @return true if position is not '#' (playable).
 * @see Diamond_X_O_Board::is_valid_position
 */
bool Diamond_X_O_Board::is_valid_position(int x, int y) {
    return (board[x][y] != '#');
}

//--------------------------------------- Diamond_X_O_UI Implementation

/**
 * @brief Constructs a Diamond_X_O_UI object.
 * @see Diamond_X_O_UI::Diamond_X_O_UI
 */
Diamond_X_O_UI::Diamond_X_O_UI() : UI<char>("Welcome to FCAI Diamond X-O Game ", 3) {
    player1 = nullptr;
    player2 = nullptr;
}

/**
 * @brief Creates a player with specified attributes.
 * @param name Player name.
 * @param symbol Player symbol ('X' or 'O').
 * @param type Player type (Human or Computer).
 * @return Pointer to created Player object.
 * @see Diamond_X_O_UI::create_player
 */
Player<char>* Diamond_X_O_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets move from player (human input or AI calculation).
 * @param player Pointer to player requesting move.
 * @return Pointer to Move object representing the selected move.
 * @see Diamond_X_O_UI::get_move
 */
Move<char>* Diamond_X_O_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        int x, y;
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        Diamond_X_O_Board* board = dynamic_cast<Diamond_X_O_Board*>(player->get_board_ptr());

        Player<char>* computer = player;
        Player<char>* human = nullptr;

        if (player1 != nullptr && player2 != nullptr) {
            human = (player == player1) ? player2 : player1;
            board->set_players(computer, human);
        }

        return board->find_best_move();
    }
}

/**
 * @brief Displays the diamond-shaped board matrix.
 * @param matrix The board matrix to display.
 * @see Diamond_X_O_UI::display_board_matrix
 */
void Diamond_X_O_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
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

/**
 * @brief Sets up two players for the game.
 * @return Array of two Player pointers.
 * @see Diamond_X_O_UI::setup_players
 */
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
