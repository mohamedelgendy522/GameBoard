#ifndef NUMERICAL_H
#define NUMERICAL_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
#include "Numerical.h"
vector<int> even={2,4,6,8};
vector<int> odd={1,3,5,7,9};
//------------------------------------------------------

Numerical::Numerical() : Board<int>(3, 3) {
    for (auto &row : board)
        for (auto &cell : row)
            cell = blank_symbol;
}
bool Numerical::update_board(Move<int>* move)  {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == blank_symbol) {
        board[x][y] = number;
        n_moves++;
        return true;
    }
    return false;
}

bool Numerical::is_win(Player<int>* player)  {
    const int sum = 15;

    auto is_ok = [&](int a, int b, int c) {
        return (a + b + c) == sum;
    };

    for (int i = 0; i < rows; ++i)
        if (is_ok(board[i][0], board[i][1], board[i][2])||
            is_ok(board[0][i], board[1][i], board[2][i]))
            return true;
    if (is_ok(board[0][0], board[1][1], board[2][2])
        || is_ok(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}

bool Numerical::is_draw(Player<int>* player)  {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical::game_is_over(Player<int>* player)  {
    return is_win(player) || is_draw(player);
}

//------------------------------------------------------
Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];

    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;

    cout << "Both players are Human in Numerical Game.\n";
    
    players[0] = create_player(name1, 1, PlayerType::HUMAN);
    players[1] = create_player(name2, 2, PlayerType::HUMAN);

    return players;
}
Numerical_UI::Numerical_UI() : UI<int>("Weclome to Numerical Game", 3) {}


Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating player: " << name << " (" << symbol << ")\n";
    return new Player<int>(name, symbol, PlayerType::HUMAN);
}

Move<int>* Numerical_UI::get_move(Player<int>* player)  {
    int x, y, num;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nEnter your move coordinates (x y): ";
        cin >> x >> y;
        cout << "Enter your number from (";
        if (player->get_symbol() % 2) {
            for (int i = 0 ; i < odd.size();i++) {
                cout<<odd[i]<<",";
            }
            cout<<" )";
            cin >> num;
            odd.erase(remove(odd.begin(), odd.end(), num), odd.end());
        }
        else {
            for (int i = 0 ; i < even.size();i++) {
                cout<<even[i]<<",";
            }
            cout<<" )";
            cin >> num;
            even.erase(remove(even.begin(), even.end(), num), even.end());
        }
    }
    return new Move<int>(x, y, num);
}

#endif // NUMERICAL_H
