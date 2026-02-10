/**
 * @file Big_XO_Tic_Tac_Toe.cpp
 * @brief Implementation of the 5×5 Big Tic-Tac-Toe (X-O) game.
 *
 * Implements:
 * - X_O_Board: 5×5 board logic, sequence counting, win/draw/game-over.
 * - XO_UI: Player creation and move input (human + AI).
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Big_XO_Tic_Tac_Toe.h"

using namespace std;

// ======================= X_O_Board Implementation =======================

/**
 * @brief Constructs a new 5×5 Big Tic-Tac-Toe board.
 *
 * Initializes all cells with the blank symbol ('.') and resets move counter.
 */
Big_XO_Board::Big_XO_Board() : Board(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Applies a move to the board if valid.
 *
 * Checks boundaries, symbol validity, cell availability, and max moves.
 * Supports deletion with symbol '\0'.
 *
 * @param move Pointer to a Move<char> object.
 * @return true if the move was applied successfully, false otherwise.
 */
bool Big_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark_raw = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid move! Position outside the board.\n";
        return false;
    }

    if (mark_raw == '\0' || mark_raw == 0) {
        if (board[x][y] == blank_symbol) return false;
        board[x][y] = blank_symbol;
        n_moves = max(0, n_moves - 1);
        return true;
    }

    char mark = static_cast<char>(toupper(static_cast<unsigned char>(mark_raw)));
    if (mark != 'X' && mark != 'O') {
        cout << "Invalid symbol. Use 'X' or 'O'.\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Invalid move! Cell already filled.\n";
        return false;
    }

    if (n_moves >= 24) {
        cout << "Game over! Maximum moves reached!\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;
    return true;
}

/**
 * @brief Counts sequences of 3 identical symbols in rows, columns, and diagonals.
 *
 * @param sym Symbol to count sequences for.
 * @return Number of sequences of 3 found.
 */
int Big_XO_Board::count_sequences(char sym) {
    sym = static_cast<char>(toupper(static_cast<unsigned char>(sym)));
    int count = 0;

    // Rows
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r][c + 1] == sym && board[r][c + 2] == sym)
                count++;

    // Columns
    for (int c = 0; c < columns; ++c)
        for (int r = 0; r <= rows - 3; ++r)
            if (board[r][c] == sym && board[r + 1][c] == sym && board[r + 2][c] == sym)
                count++;

    // Main diagonals
    for (int r = 0; r <= rows - 3; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r + 1][c + 1] == sym && board[r + 2][c + 2] == sym)
                count++;

    // Anti-diagonals
    for (int r = 2; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r - 1][c + 1] == sym && board[r - 2][c + 2] == sym)
                count++;

    return count;
}

/**
 * @brief Determines if the given player has won the game.
 *
 * Win occurs if the player has more sequences of 3 than the opponent after all moves.
 *
 * @param player Player to check.
 * @return true if the player wins.
 */
bool Big_XO_Board::is_win(Player<char>* player) {
    if (n_moves < 24) return false;

    int xSeq = count_sequences('X');
    int oSeq = count_sequences('O');

    char sym = static_cast<char>(toupper(static_cast<unsigned char>(player->get_symbol())));
    return (sym == 'X' && xSeq > oSeq) || (sym == 'O' && oSeq > xSeq);
}

/**
 * @brief Determines if the game ended in a draw.
 *
 * Draw occurs if both X and O have equal sequences after all moves.
 *
 * @param player Player reference (unused).
 * @return true if draw.
 */
bool Big_XO_Board::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;
    return count_sequences('X') == count_sequences('O');
}

/**
 * @brief Checks if the game is over.
 *
 * Game is over after 24 moves.
 *
 * @param player Player reference (unused).
 * @return true if game ended.
 */
bool Big_XO_Board::game_is_over(Player<char>* player) {
    return n_moves >= 24;
}

/**
 * @brief Displays scores (optional: sequence counts for X and O).
 */
void Big_XO_Board::display_scores() {
    cout << "X sequences: " << count_sequences('X') << "\n";
    cout << "O sequences: " << count_sequences('O') << "\n";
}

// ======================= XO_UI Implementation =======================

/**
 * @brief Constructs the Big X-O UI with welcome message.
 */
Big_XO_UI::Big_XO_UI() : UI<char>("Welcome to 5 x 5 Tic Tac Toe X-O Game", 3) {}

/**
 * @brief Creates a human or AI player.
 *
 * @param name Player name.
 * @param symbol Player symbol ('X' or 'O').
 * @param type Player type (HUMAN/COMPUTER).
 * @return Pointer to new Player object.
 */
Player<char>* Big_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer(AI)")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the next move from a player (human input or AI).
 *
 * @param player Player making the move.
 * @return Pointer to Move<char> object, or nullptr if game over.
 */
Move<char>* Big_XO_UI::get_move(Player<char>* player) {
    Big_XO_Board* xb = dynamic_cast<Big_XO_Board*>(player->get_board_ptr());
    if (xb && xb->get_n_moves() >= 24) {
        cout << "Game over! No more moves allowed.\n";
        return nullptr;
    }

    // ---------------- HUMAN INPUT ----------------
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << player->get_name() << " (" << player->get_symbol() << ") enter your move x y: ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    // ---------------- AI LOGIC ----------------
    Board<char>* b = player->get_board_ptr();
    auto mat = b->get_board_matrix();
    char AI = player->get_symbol();
    char OP = (AI == 'X' ? 'O' : 'X');

    int bestX = -1, bestY = -1, bestScore = -1;

    auto countSeqAt = [&](int i, int j, char sym) -> int {
        int cnt = 0;
        int dx[] = {1,0,1,1};
        int dy[] = {0,1,1,-1};

        for (int dir = 0; dir < 4; dir++) {
            int c = 1;
            int nx = i + dx[dir], ny = j + dy[dir];

            while (nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && mat[nx][ny] == sym) {
                c++; nx += dx[dir]; ny += dy[dir];
            }

            nx = i - dx[dir]; ny = j - dy[dir];
            while (nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && mat[nx][ny] == sym) {
                c++; nx -= dx[dir]; ny -= dy[dir];
            }

            if (c >= 3) cnt++;
        }
        return cnt;
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == '.') {
                mat[i][j] = AI;
                int scoreAI = countSeqAt(i, j, AI);
                mat[i][j] = '.';

                mat[i][j] = OP;
                int scoreOP = countSeqAt(i, j, OP);
                mat[i][j] = '.';

                int totalScore = scoreAI*2 + scoreOP;
                if (totalScore > bestScore) { bestScore = totalScore; bestX = i; bestY = j; }
            }

    if (bestX == -1) {
        if (mat[2][2] == '.') { bestX = 2; bestY = 2; }
        else {
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    if (mat[i][j] == '.') { bestX = i; bestY = j; goto RETURN_MOVE; }
        }
    }

RETURN_MOVE:
    cout << "AI plays at: " << bestX << " " << bestY << "\n";
    return new Move<char>(bestX, bestY, AI);
}
