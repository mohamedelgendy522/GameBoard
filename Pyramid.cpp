#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Pyramid.h"
#include <bits/stdc++.h>
using namespace std;
//--------------------------------------- IMPLEMENTATION



//--------------------------------------- X_O_Board Implementation
map<pair<int,int>,bool> check;


Pyramid::Pyramid() : Board(5, 5) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = '#';
        }
    }
    board[2][2] = '.';
    check[{2,2}] = true;

    for (int i = 1; i < 4; i++) {
        board[3][i] = '.';
        check[{3,i}] = true;
    }

    for (int i = 0; i < 5; i++) {
        check[{4,i}] = true;
        board[4][i] = '.';
    }


}




bool Pyramid::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    if (!check[{x,y}] || board[x][y] != '.') {
        return false;
    }
    board[x][y] = mark;
    return true;
}





bool Pyramid::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // check diagonal
    if ((all_equal(board[4][0],board[3][1],board[2][2]) && board[4][0] == sym)
        || (all_equal(board[4][4],board[3][3],board[2][2]) && board[4][4] == sym)) return true;

    // check vertical
    if ((all_equal(board[4][2],board[3][2],board[2][2]) && board[4][2] == sym)) return true;

    // check horizontally
    if ((all_equal(board[3][1],board[3][2],board[3][3]) && board[3][3] == sym)) return true;

    for (int i = 0 ; i < 3; i++) {
        if ((all_equal(board[4][i],board[4][i + 1],board[4][i + 2]) && board[4][i] == sym))
            return true;
    }

    return false;

}

bool Pyramid::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- Pyramid_UI Implementation

Pyramid_UI::Pyramid_UI() : UI<char>("Weclome to Pyramid X-O Game ", 3) {}




Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}



Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y";
        cin >> x >> y;
    }
     else if (player->get_type() == PlayerType::COMPUTER) {
         Board<char>* b = player->get_board_ptr();

         for (int i = 0; i < b->get_rows(); i++) {
            for (int j = 0; j < b->get_columns(); j++) {

                if (check[{i, j}] && b->get_cell(i, j) == '.') {
                    return new Move<char>(i, j, player->get_symbol());
                }

            }
        }
     }
    return new Move<char>(x, y, player->get_symbol());
}
