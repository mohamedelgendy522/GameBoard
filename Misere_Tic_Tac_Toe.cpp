/**
 * @file Misere_Tic_Tac_Toe.cpp
 * @brief Implementation of Misère Tic-Tac-Toe classes.
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 *
 * This file contains the implementation of:
 * - Inverse_X_O_Board class methods
 * - Inverse_X_O_UI class methods
 */

#include <iostream>
#include <iomanip>
#include <cctype>
#include "Misere_Tic_Tac_Toe.h"
using namespace std;

//--------------------------------------- Inverse_X_O_Board Implementation

/**
 * @brief Constructs an Inverse_X_O_Board with 3x3 dimensions.
 * @details Initializes all cells with the blank symbol ('.').
 */
Inverse_X_O_Board::Inverse_X_O_Board() : Board(3,3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Updates the board with a move.
 * @param move Pointer to Move object containing coordinates and symbol.
 * @return true if move was valid and applied, false otherwise.
 * @see Inverse_X_O_Board::update_board
 */
bool Inverse_X_O_Board::update_board(Move<char>* move) {
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

/**
 * @brief Checks if player has lost (made three in a row).
 * @param player Pointer to the player to check.
 * @return true if player has three consecutive symbols, false otherwise.
 * @see Inverse_X_O_Board::is_lose
 */
bool Inverse_X_O_Board::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return (a == b && b == c && a != blank_symbol);
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

/**
 * @brief Checks if game is a draw.
 * @param player Pointer to the player (unused, for interface compatibility).
 * @return true if board is full and no player has lost, false otherwise.
 * @see Inverse_X_O_Board::is_draw
 */
bool Inverse_X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Checks if game is over.
 * @param player Pointer to the player.
 * @return true if game is won or drawn, false otherwise.
 * @see Inverse_X_O_Board::game_is_over
 */
bool Inverse_X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Checks if current state is terminal (game over).
 * @return true if game is over, false otherwise.
 * @see Inverse_X_O_Board::is_terminal
 */
bool Inverse_X_O_Board::is_terminal() {
    return is_lose(computer_player) || is_lose(human_player) || n_moves == 9;
}

/**
 * @brief Sets player pointers for the board.
 * @param comp Pointer to computer player.
 * @param human Pointer to human player.
 * @see Inverse_X_O_Board::set_players
 */
void Inverse_X_O_Board::set_players(Player<char>* comp, Player<char>* human) {
    computer_player = comp;
    human_player = human;
}

/**
 * @brief Evaluates the board state for AI.
 * @return 10 if human loses, -10 if computer loses, 0 otherwise.
 * @see Inverse_X_O_Board::evaluate
 */
int Inverse_X_O_Board::evaluate() {
    if(is_lose(computer_player))
        return -10;

    if(is_lose(human_player)) {
        return 10;
    }

    return 0;
}

/**
 * @brief Minimax algorithm with alpha-beta pruning.
 * @param is_maximizing true if current player is computer, false if human.
 * @param alpha Alpha value for pruning.
 * @param beta Beta value for pruning.
 * @return Best evaluation score for current board state.
 * @see Inverse_X_O_Board::minimax
 */
int Inverse_X_O_Board::minimax(bool is_maximizing, int alpha, int beta) {
    // Base case
    if (is_terminal()) {
        return evaluate();
    }

    if (is_maximizing) {
        int max_eval = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == blank_symbol) {
                    // Try move
                    board[i][j] = computer_player->get_symbol();
                    n_moves++;

                    int eval = minimax(false, alpha, beta);

                    // Undo move
                    board[i][j] = blank_symbol;
                    n_moves--;

                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) break; // alpha-beta pruning
                }
            }
        }
        return max_eval;
    } else {
        int min_eval = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == blank_symbol) {
                    // Try opponent's move
                    board[i][j] = human_player->get_symbol();
                    n_moves++;

                    int eval = minimax(true, alpha, beta);

                    // Undo move
                    board[i][j] = blank_symbol;
                    n_moves--;

                    min_eval = min(min_eval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) break; // alpha-beta pruning
                }
            }
        }
        return min_eval;
    }
}

/**
 * @brief Finds the best move for computer using minimax.
 * @return Pointer to best Move object, or any valid move if none found.
 * @see Inverse_X_O_Board::find_best_move
 */
Move<char>* Inverse_X_O_Board::find_best_move() {
    int best_score = -1000;
    Move<char>* best_move = nullptr;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == blank_symbol) {
                // Try move
                board[i][j] = computer_player->get_symbol();
                n_moves++;

                int score = minimax(false,-1000,1000);

                // Undo move
                board[i][j] = blank_symbol;
                n_moves--;

                if (score > best_score) {
                    best_score = score;
                    best_move = new Move<char>(i, j, computer_player->get_symbol());
                }
            }
        }
    }
    if (best_move == nullptr) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == blank_symbol) {
                    return new Move<char>(i, j, computer_player->get_symbol());
                }
            }
        }
    }
    return best_move;
}

//--------------------------------------- Inverse_X_O_UI Implementation

/**
 * @brief Gets move from player (human input or AI calculation).
 * @param player Pointer to player requesting move.
 * @return Pointer to Move object representing the selected move.
 * @see Inverse_X_O_UI::get_move
 */
Move<char>* Inverse_X_O_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        int x, y;
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        Inverse_X_O_Board* board = dynamic_cast<Inverse_X_O_Board*>(player->get_board_ptr());

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
 * @brief Constructs an Inverse_X_O_UI object.
 * @see Inverse_X_O_UI::Inverse_X_O_UI
 */
Inverse_X_O_UI::Inverse_X_O_UI() : UI<char>("Welcome to FCAI Misere X-O Game ", 3) {
    player1 = nullptr;
    player2 = nullptr;
}

/**
 * @brief Creates a player with specified attributes.
 * @param name Player name.
 * @param symbol Player symbol ('X' or 'O').
 * @param type Player type (Human or Computer).
 * @return Pointer to created Player object.
 * @see Inverse_X_O_UI::create_player
 */
Player<char>* Inverse_X_O_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Sets up two players for the game.
 * @return Array of two Player pointers.
 * @see Inverse_X_O_UI::setup_players
 */
Player<char> **Inverse_X_O_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);
    player1 = players[0];  // Save player 1

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);
    player2 = players[1];  // Save player 2

    return players;
}