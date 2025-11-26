#include "BoardGame_Classes.h"
class Inverse_X_O_Board : public Board<char>{
private:

    char blank_symbol = '.';

public:

    Inverse_X_O_Board();
    bool update_board(Move<char>* move);
    virtual bool is_win(Player<char>*) { return false; } ;
    bool is_lose(Player<char>*) ;
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Inverse_X_O_UI : public UI<char> {
  public:
    Inverse_X_O_UI();
    ~Inverse_X_O_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};




