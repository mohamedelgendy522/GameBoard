//
// Created by mizot on 11/12/2025.
//

#ifndef NUMERICAL_H
#define NUMERICAL_H

#endif //NUMERICAL_H
#include "BoardGame_Classes.h"
using namespace std;

class Numerical: public Board<int> {
private:
    int blank_symbol = 0;
public:
    Numerical();

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
    Player<int>* create_player(string& name, int symbol, PlayerType type);
    Player<int>** setup_players();

    Move<int>* get_move(Player<int>* player);
};
