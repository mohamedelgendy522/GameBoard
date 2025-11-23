#include "BoardGame_Classes.h"
#include<iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ---------------- Word_Board ----------------
class Word_Board : public Board<char> {
public:
    Word_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;

    char get_cell(int x, int y) const { return board[x][y]; }
};

// ---------------- Word_UI ----------------
class Word_UI : public UI<char> {
public:
    Word_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board(Board<char>* board);
};

