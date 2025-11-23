#include "Word_tic_tac_toe.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include <iomanip>

using namespace std;

unordered_set<string> dict;

void load_dict() {
    ifstream fin("dic.txt");
    string w;
    while (fin >> w) {
        dict.insert(w);
    }
}

// ---------------- Word_Board ----------------
Word_Board::Word_Board() : Board<char>(3, 3) {
    load_dict();

    for (auto& row : board)
        for (auto& cell : row)
            cell = '.'; 
    n_moves = 0;
}

bool Word_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char val = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != '.')
        return false;

    board[x][y] = val;
    n_moves++;
    return true;
}

bool Word_Board::is_win(Player<char>* player) {
    auto ValidWord = [&](char a, char b, char c) -> string {
        string s;
        s.push_back(a);  
        s.push_back(b);
        s.push_back(c);
        return s;
    };

    // check rows and cols
    for (int i = 0; i < rows; ++i) {
        string rowWord = ValidWord(board[i][0], board[i][1], board[i][2]);
        if (dict.count(rowWord)) return true;

        string colWord = ValidWord(board[0][i], board[1][i], board[2][i]);
        if (dict.count(colWord)) return true;
    }

    // diagonals
    string d1 = ValidWord(board[0][0], board[1][1], board[2][2]);
    if (dict.count(d1)) return true;

    string d2 = ValidWord(board[0][2], board[1][1], board[2][0]);
    if (dict.count(d2)) return true;

    return false;
}

bool Word_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(nullptr));
}

bool Word_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool Word_Board::is_lose(Player<char>* player) {
    return false;
}

// ---------------- Word_UI ----------------
Word_UI::Word_UI() : UI<char>("Welcome to Word Tic-tac-toe Game", 3) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Player<char>* Word_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Word_UI::get_move(Player<char>* player) {
    int x, y;
    char val;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", please enter your move (x y char): ";
        cin >> x >> y >> val;
        val = toupper(val);
    } 
    else {
        bool found = false;
        for (int attempts = 0; attempts < 50 && !found; ++attempts) {
            x = rand() % 3;
            y = rand() % 3;
            Board<char>* bp = player->get_board_ptr();
            if (bp && bp->get_board_matrix()[x][y] == '.') {
                found = true;
                break;
            }
        }
        if (!found) { 
            Board<char>* bp = player->get_board_ptr();
            if (bp) {
                auto mat = bp->get_board_matrix();
                for (int i = 0; i < 3 && !found; ++i)
                    for (int j = 0; j < 3 && !found; ++j)
                        if (mat[i][j] == '.') { x = i; y = j; found = true; }
            }
        }
        val = 'A' + (rand() % 26);
        cout << "Computer chooses: " << x << " " << y << " " << val << endl;
    }
    return new Move<char>(x, y, val);
}

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
