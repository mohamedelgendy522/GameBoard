#pragma once
#include "BoardGame_Classes.h"
#include <set>
using namespace std;
class Numerical_Board : public Board<int> {
private:
    set<int> used_numbers;

public:
    Numerical_Board();

    bool update_board(Move<int>* move);

    bool is_win(Player<int>* player);
    
    bool is_lose(Player<int>*) { return false; };

    bool is_draw(Player<int>* player);

    bool game_is_over(Player<int>* player);
};


class Numerical_UI : public UI<int> {
public:
    
    Numerical_UI();

    ~Numerical_UI() {};

    Player<int>* create_player(string& name, int symbol, PlayerType type = PlayerType::HUMAN);
    Move<int>* get_move(Player<int>* player);
    Player<int>** setup_players();
};



