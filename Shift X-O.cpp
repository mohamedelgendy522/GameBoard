#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Shift XO.h"
#include <bits/stdc++.h>

using namespace std;

//--------------------------------------- X_O_Board Implementation
static string shift;
vector<vector<char>> Matrix(4, vector<char>(4, '.'));

X_O_Shift::X_O_Shift() : Board(4, 4) {
    vector<pair<int,int>> O={{0,0},{0,2},{3,1},{3,3}};
    vector<pair<int,int>> X={{0,1},{0,3},{3,0},{3,2}};
    map<pair<int,int>,bool> Oo,Xx;

    for (auto i : O) Oo[i]=true;
    for (auto i : X) Xx[i]=true;

    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if (Oo[{i,j}]) {
                board[i][j] = 'O';
            }
            else if (Xx[{i,j}]) {
                board[i][j] = 'X';
            }
            else {
                board[i][j] = blank_symbol;
            }
        }
    }
    Matrix = board;
}

bool X_O_Shift::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    string s =  shift;
    if (x < 0 || x >= rows || y < 0 || y >= columns ) {
        cout<<"Out of bounds!"<<endl;
        return false;
    }
    if (board[x][y] != mark) {
        cout<<"This is not your piece!"<<endl;
        return false;
    }
    if (shift=="Right") {
        if (y + 1 >= columns || board[x][y + 1] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        else {
            board[x][y] = '.';
            board[x][y+1] = mark;
        }
    }
    else if (shift=="Left") {
        if (y - 1 < 0 || board[x][y - 1] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        else {
            board[x][y] = '.';
            board[x][y-1] = mark;
        }
    }
    else if (shift=="Down") {
        if (x + 1 >= rows || board[x + 1][y] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        else {
            board[x][y] = '.';
            board[x + 1][y] = mark;
        }
    }
    else if (shift=="Up") {
        if (x - 1 < 0 || board[x - 1][y] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        else {
            board[x][y] = '.';
            board[x - 1][y] = mark;
        }
    }
    Matrix = board;
    return true;
}

bool X_O_Shift::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    auto all_equal_4 = [&](char a, char b, char c,char d) {
        if (a==b && b==c && a!=blank_symbol && a == sym) return true;
        if (b==c && c==d && d!=blank_symbol && b == sym) return true;
        return false;
    };

    auto all_equal_3 = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol && a == sym;
    };
    // // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if (all_equal_4(board[i][0], board[i][1], board[i][2],board[i][3])||
            all_equal_4(board[0][i], board[1][i], board[2][i],board[3][i]))
            return true;
    }

    if ((all_equal_3(board[2][0], board[1][1], board[0][2]) && board[0][2] == sym)
        || (all_equal_3(board[3][1],board[2][2],board[1][3])&& board[3][1] == sym))
        return true;

    if ((all_equal_3(board[1][0], board[2][1], board[3][2]) && board[1][0] == sym)
        || (all_equal_3(board[0][1], board[1][2],board[2][3]) && board[0][1] == sym))
        return true;

    if (all_equal_4(board[0][0],board[1][1],board[2][2],board[3][3])
        || all_equal_4(board[0][3],board[1][2],board[2][1],board[3][0]))
        return true;

    return false;
}

bool X_O_Shift::is_draw(Player<char>* player) {
    return (n_moves == 12 && !is_win(player));
}

bool X_O_Shift::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);

}

X_O_Shift_UI::X_O_Shift_UI() : UI<char>("Weclome to FCAI Shift X-O ", 3) {}

Player<char>* X_O_Shift_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Move<char>* X_O_Shift_UI::get_move(Player<char>* player) {
    int x,y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout<<"Choose the position of the piece you want to move : ";
        cin>>x>>y;
        cout<<"Select Your Move (Right , Left , Up , Down) ";
        string s;
        cin>>s;
        shift = s;
    }
    if (player->get_type() == PlayerType::COMPUTER) {
        char sym = player->get_symbol();

        vector<string> dirs = {"Right", "Left", "Down", "Up"};

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                if (Matrix[i][j] != sym) continue;

                for (auto d : dirs) {
                    int nx = i, ny = j;

                    if (d == "Right")  ny++;
                    if (d == "Left")   ny--;
                    if (d == "Down")   nx++;
                    if (d == "Up")     nx--;

                    if (nx >= 0 && nx < 4 &&
                        ny >= 0 && ny < 4 &&
                        Matrix[nx][ny] == '.') {

                        shift = d;
                        return new Move<char>(i, j, sym);
                        }
                }
            }
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}
