#ifndef BIG_XO_TIC_TAC_TOE_H
#define BIG_XO_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <queue>
using namespace std;


class X_O_Board : public Board<char> {
private:
    char blank_symbol = '.';
	queue<std::pair<int, int>> history;// To track the order of moves
public:
    X_O_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; };


    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player);
};



class XO_UI : public UI<char> {
public:

    XO_UI();

    ~XO_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    virtual Move<char>* get_move(Player<char>* player);
};

#endif 

