#include <iostream>
#include <iomanip>
#include <set>
#include "Numerical_Tic_Tac_Toe.h"
#include "algorithm"

using namespace std;
Numerical_Board::Numerical_Board() : Board(3, 3) {
    board.assign(3, vector<int>(3, 0)); // initialize 3x3 with zeros
    used_numbers.clear();
}

vector<int> even = {2,4,6,8};
vector<int> odd = {1,3,5,7,9};


bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;

    // Cell must be empty and number must not be reused
    if (board[x][y] != 0 || used_numbers.count(num))
        return false;

    board[x][y] = num;
    used_numbers.insert(num);
    n_moves++;
    return true;
}

bool Numerical_Board::is_win(Player<int>* player) {
    
    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((board[i][0] + board[i][1] + board[i][2]) == 15) return true;
        if ((board[0][i] + board[1][i] + board[2][i]) == 15) return true;
    }

    // diagonals
    if ((board[0][0] + board[1][1] + board[2][2]) == 15) return true;
    if ((board[0][2] + board[1][1] + board[2][0]) == 15) return true;

    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

Numerical_UI::Numerical_UI() : UI<int>("Weclome to Numerical Tic-Tac-Toe Game", 3) {}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating player: " << name;
    if (symbol == 1)
        cout << " (Odd numbers)\n";
    else
        cout << " (Even numbers)\n";

    return new Player<int>(name, symbol, PlayerType::HUMAN);
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y, num;
    int sym = player->get_symbol();

    cout << "\n" << player->get_name();

    cout << "Enter your move position x,y (0-2):\n";
    cin >> x >> y;
    cout<<"Enter number from (";
    if (sym) {
        for (int i = 0; i < odd.size(); ++i) {
            cout<<odd[i]<<",";
        }
        cout<<")";
        cin>>num;
        auto it = find(odd.begin(), odd.end(), num);
        if (it != odd.end()) {
            odd.erase(remove(odd.begin(), odd.end(), num), odd.end());
        }
        else {
            cout<<"Enter another number from(";
            for (int i = 0; i < odd.size(); ++i) {
                cout<<odd[i]<<",";
            }
            cout<<")";
            cin>>num;
            odd.erase(remove(odd.begin(), odd.end(), num), odd.end());
        }
    }
    else {
        for (int i = 0; i < even.size(); ++i) {
            cout<<even[i]<<",";
        }
        cout<<")";
        cin>>num;
        auto it = find(even.begin(), even.end(), num);
        if (it != even.end()) {
            even.erase(remove(even.begin(), even.end(), num), even.end());
        }
        else {
            cout<<"Enter another number from(";
            for (int i = 0; i < even.size(); ++i) {
                cout<<even[i]<<",";
            }
            cout<<")";
            cin>>num;
            even.erase(remove(even.begin(), even.end(), num), even.end());
        }
    }
    return new Move<int>(x, y, num);
}
Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];

    string nameOdd = get_player_name("Odd Player");
    players[0] = create_player(nameOdd, 1);

    string nameEven = get_player_name("Even Player");
    players[1] = create_player(nameEven, 0);

    return players;
}

