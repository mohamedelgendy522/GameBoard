#ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
using namespace std;

class Obstacles_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacles = '#';
public:
    Obstacles_XO_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; };

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
};

class Obstacles_XO_UI : public UI<char> {
public:

    Obstacles_XO_UI();

    ~Obstacles_XO_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);
};
#endif // OBSTACLES_TIC_TAC_TOE_H

