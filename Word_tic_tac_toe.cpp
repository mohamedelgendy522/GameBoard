/**
 * @file Word_tic_tac_toe.cpp
 * @brief Implements the Word Tic-Tac-Toe board and UI logic.
 *
 * This file contains:
 * - Dictionary loading  
 * - Word_Board implementation (move handling, win/draw detection)  
 * - Word_UI implementation (player creation, move input, AI logic, board printing)
 */

#include "Word_tic_tac_toe.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include <iomanip>

using namespace std;

/** 
 * @brief Global dictionary storing valid 3-letter words.
 */
unordered_set<string> dict;

/**
 * @brief Loads dictionary words from a file into the global hash set.
 *
 * Reads words from "dic.txt" and stores each into @ref dict.
 * This allows O(1) lookup for checking valid words.
 */
void load_dict() {
    ifstream fin("dic.txt");
    string w;
    while (fin >> w) {
        dict.insert(w);
    }
}

/*============================================================
                     Word_Board Implementation
=============================================================*/

/**
 * @brief Constructs a 3×3 Word Tic-Tac-Toe board.
 *
 * Initializes:
 * - Dictionary  
 * - All cells to '.'  
 * - Move counter to 0  
 */
Word_Board::Word_Board() : Board<char>(3, 3) {
    load_dict();

    for (auto& row : board)
        for (auto& cell : row)
            cell = '.'; 

    n_moves = 0;
}

/**
 * @brief Applies a user's move if the position is valid.
 *
 * Checks:
 * - If coordinates are inside the board  
 * - If the target cell is empty  
 *
 * @param move Move containing x, y, and the character.
 * @return true if the move is accepted, false otherwise.
 */
bool Word_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char val = move->get_symbol();

    // Bounds check
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "\n Invalid move! Position (" << x << ", " << y << ") is outside the board.\n";
        return false;
    }

    // Occupied cell check
    if (board[x][y] != '.') {
        cout << "\n Invalid move! Cell (" << x << ", " << y << ") is already filled.\n";
        return false;
    }

    board[x][y] = val;
    n_moves++;

    return true;
}

/**
 * @brief Determines if placing any 3-letter sequence forms a valid dictionary word.
 *
 * Checks:
 * - All rows  
 * - All columns  
 * - Both diagonals  
 *
 * @param player Unused (word completion doesn't depend on player symbol).
 * @return true if any line forms a valid word.
 */
bool Word_Board::is_win(Player<char>* player) {
    auto ValidWord = [&](char a, char b, char c) -> string {
        string s;
        s.push_back(a);
        s.push_back(b);
        s.push_back(c);
        return s;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        string rowWord = ValidWord(board[i][0], board[i][1], board[i][2]);
        if (dict.count(rowWord)) return true;

        string colWord = ValidWord(board[0][i], board[1][i], board[2][i]);
        if (dict.count(colWord)) return true;
    }

    // Check diagonals
    string d1 = ValidWord(board[0][0], board[1][1], board[2][2]);
    if (dict.count(d1)) return true;

    string d2 = ValidWord(board[0][2], board[1][1], board[2][0]);
    if (dict.count(d2)) return true;

    return false;
}

/**
 * @brief Checks for a draw.
 *
 * A draw occurs when:
 * - All 9 cells are filled  
 * - No valid word has been formed  
 */
bool Word_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(nullptr));
}

/**
 * @brief Determines whether the game has ended.
 *
 * The game ends when:
 * - A valid word is formed (win)  
 * - The board is full (draw)  
 */
bool Word_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Word Tic-Tac-Toe does not implement losing conditions.
 *
 * @return Always false.
 */
bool Word_Board::is_lose(Player<char>* player) {
    return false;
}

/*============================================================
                         Word_UI Implementation
=============================================================*/

/**
 * @brief Constructs the UI for the Word Tic-Tac-Toe game.
 *
 * Seeds the random generator for AI randomness.
 */
Word_UI::Word_UI() : UI<char>("Welcome to Word Tic-tac-toe Game", 3) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 * @brief Creates a player and prints a creation message.
 *
 * @param name Player name.
 * @param symbol Display symbol.
 * @param type HUMAN or COMPUTER.
 * @return Newly allocated Player<char>.
 */
Player<char>* Word_UI::create_player(string& name, char symbol, PlayerType type) {
    static int playerNumber = 1;

    cout << "Creating Player " << playerNumber
         << " (" << (type == PlayerType::HUMAN ? "Human" : "Computer") << "): "
         << name << "\n";

    playerNumber++;
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Retrieves the next move from either a human or AI player.
 *
 * HUMAN:
 * - Prompts user for x, y, and a character  
 *
 * COMPUTER:
 * - Tries all possible empty spots and letters to find an immediate winning move  
 * - If none found, selects a random move  
 *
 * @param player Player whose move is requested.
 * @return Newly created Move<char>.
 */
Move<char>* Word_UI::get_move(Player<char>* player) {
    int x, y;
    char val;

    // HUMAN MOVE
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", please enter your move (x,y,char): ";
        cin >> x >> y >> val;
        val = toupper(val);
    }

    else {  // COMPUTER MOVE
        Word_Board* board = dynamic_cast<Word_Board*>(player->get_board_ptr());
        bool found = false;

        // Try to find a winning move
        for (int i = 0; i < board->get_rows() && !found; ++i) {
            for (int j = 0; j < board->get_columns() && !found; ++j) {
                if (board->get_cell(i, j) == '.') {
                    for (char c = 'A'; c <= 'Z' && !found; ++c) {

                        Word_Board tempBoard = *board;

                        Move<char> tempMove(i, j, c);
                        tempBoard.update_board(&tempMove);

                        if (tempBoard.is_win(nullptr)) {
                            x = i; y = j; val = c;
                            found = true;
                        }
                    }
                }
            }
        }

        // No winning move found → play random
        if (!found) {
            for (int attempts = 0; attempts < 50 && !found; ++attempts) {
                x = rand() % 3;
                y = rand() % 3;
                if (board->get_cell(x, y) == '.') {
                    val = 'A' + (rand() % 26);
                    found = true;
                }
            }

            // Safety fallback
            if (!found) {
                for (int i = 0; i < 3 && !found; i++)
                    for (int j = 0; j < 3 && !found; j++)
                        if (board->get_cell(i, j) == '.') {
                            x = i; y = j;
                            val = 'A' + (rand() % 26);
                            found = true;
                        }
            }
        }

        cout << "Computer chooses: " << x << " " << y << " " << val << endl;
    }

    return new Move<char>(x, y, val);
}

/**
 * @brief Prints the board in a clean 3×3 grid format.
 *
 * @param b Pointer to the board.
 */
void Word_UI::display_board(Board<char>* b) {
    Word_Board* board = dynamic_cast<Word_Board*>(b);
    cout << "\nCurrent Board:\n";

    for (int i = 0; i < board->get_rows(); ++i) {
        for (int j = 0; j < board->get_columns(); ++j) {
            char val = board->get_cell(i, j);
            cout << setw(4) << val;
        }
        cout << "\n";
    }
}
