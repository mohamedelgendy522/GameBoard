#ifndef SUS_H
#define SUS_H
#include "BoardGame_Classes.h"
using namespace std;
class SUS_Board : public Board<char>{
private:
	char blank_symbol = '.';

    int score_S = 0;
    int score_U = 0;

    bool main_diagonal_s = false;
    bool main_diagonal_u = false;

    bool anti_diagonal_s = false;
    bool anti_diagonal_u = false;

    bool row_u[3] = { false,false ,false };
    bool row_s[3] = { false,false ,false };

    bool column_u[3] = { false,false ,false };
    bool column_s[3] = { false,false ,false };
public:

    SUS_Board();

    bool update_board(Move<char>* move);

    void update_scores(Player<char>* player);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>* player);

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
    
};

class SUS_UI : public UI<char> {
public:
    
    SUS_UI();

    ~SUS_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    virtual Move<char>* get_move(Player<char>* player);

    Player<char>** setup_players();
};
#endif // SUS_H
