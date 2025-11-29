#include "BoardGame_Classes 2.3v.h"

class Diamond_X_O_Board : public Board<char> {

    char blank_symbol = '_';

public:

    Diamond_X_O_Board() ;
    bool update_board(Move<char>* move);
    virtual bool is_win(Player<char>*)  ;
    bool is_lose(Player<char>*) { return false; } ;
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    bool is_valid_position(int x, int y);

};
class Diamond_X_O_UI : public UI<char> {
public:
    Diamond_X_O_UI();
    ~Diamond_X_O_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};
