#include <iostream>
#include <iomanip>
#include <cctype>
#include "Infinity.h"

using namespace std;

// ---------------- Infinity_Board ----------------

X_O_Board::X_O_Board() : Board(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool X_O_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = toupper(move->get_symbol());

	if (x < 0 || x >= rows || y < 0 || y >= columns)// Out of bounds
        return false;

	if (mark == 0) {// Undo move
		if (board[x][y] == blank_symbol) return false; 

        board[x][y] = blank_symbol;
        n_moves = max(0, n_moves - 1);

        queue<pair<int, int>> newq;
        while (!history.empty()) {
            auto p = history.front(); history.pop();
            if (!(p.first == x && p.second == y)) newq.push(p);
        }
        history = std::move(newq);
        return true;
    }

    if (board[x][y] != blank_symbol)
        return false;

    static int moveCounter = 0;

    if (moveCounter > 0 && (moveCounter % 3) == 0 && !history.empty()) {
        auto oldest = history.front();
        history.pop();
        int ox = oldest.first;
        int oy = oldest.second;

        if (board[ox][oy] != blank_symbol) {
            board[ox][oy] = blank_symbol;
            n_moves = std::max(0, n_moves - 1);
        }
    }

    board[x][y] = mark;
    n_moves++;
    history.push({ x, y });

    moveCounter++;

    return true;
}

bool X_O_Board::is_win(Player<char>* player)
{
    char sym = player->get_symbol();

    auto eq = [&](char a, char b, char c) {
        return (a == sym && b == sym && c == sym);
        };

    // Rows + Columns
    for (int i = 0; i < 3; i++) {
        if (eq(board[i][0], board[i][1], board[i][2])) return true;
        if (eq(board[0][i], board[1][i], board[2][i])) return true;
    }

    // Diagonals
    if (eq(board[0][0], board[1][1], board[2][2])) return true;
    if (eq(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

bool X_O_Board::is_draw(Player<char>* player)
{
    return false;
}

bool X_O_Board::game_is_over(Player<char>* player)
{
    return is_win(player);
}


// ---------------- Infinity_UI ----------------

XO_UI::XO_UI() : UI<char>("Welcome to Infinity Tic-Tac-Toe (3x3)", 2) {}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_UI::get_move(Player<char>* player) {

    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name()
            << " (" << player->get_symbol()
            << ") enter your move x y (0 to 4): ";
        cin >> x >> y;
    }
    else {

        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }

    return new Move<char>(x, y, player->get_symbol());
}
