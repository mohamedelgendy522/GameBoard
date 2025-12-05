#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Shift X0.h"
#include <bits/stdc++.h>

using namespace std;

//----------------------------------------------------------
// Global game helpers for Shift X-O
//----------------------------------------------------------

/**
 * @brief Stores the direction chosen for shifting a piece
 * (Right, Left, Up, Down). Used by update_board().
 */
static string shift;

/**
 * @brief A 4×4 matrix representing the current board state.
 *
 * This is used mainly by the computer player to find valid moves.
 * Updated every turn to match the internal board[][].
 */
vector<vector<char>> Matrix1(4, vector<char>(4, '.'));

//----------------------------------------------------------
// X_O_Shift Board Implementation
//----------------------------------------------------------

/**
 * @brief Constructs a Shift X-O board (4×4) with predefined positions.
 *
 * Initial layout:
 *  - Four 'O' pieces in fixed positions
 *  - Four 'X' pieces in fixed positions
 *  - The rest are empty '.'
 *
 * After initialization, Matrix1 is synchronized with board[][]
 */
X_O_Shift::X_O_Shift() : Board(4, 4) {
    vector<pair<int,int>> O={{0,0},{0,2},{3,1},{3,3}};
    vector<pair<int,int>> X={{0,1},{0,3},{3,0},{3,2}};
    map<pair<int,int>,bool> Oo,Xx;

    for (auto i : O) Oo[i]=true;
    for (auto i : X) Xx[i]=true;

    // Fill board with O/X pieces based on fixed starting positions
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
    Matrix1 = board;
}

/**
 * @brief Applies a shift move to the board.
 *
 * Rules:
 *  - Player selects one of their own pieces.
 *  - Player chooses a direction: Right / Left / Up / Down.
 *  - Piece shifts by exactly 1 cell if the destination is inside bounds & empty.
 *
 * @param move Move<char> containing (x, y) coordinates + player's symbol.
 * @return true if the shift is valid and applied, false otherwise.
 */
bool X_O_Shift::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    string s =  shift;

    // Validate inside board bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns ) {
        cout<<"Out of bounds!"<<endl;
        return false;
    }

    // Player must move their own piece
    if (board[x][y] != mark) {
        cout<<"This is not your piece!"<<endl;
        return false;
    }

    // Movement logic based on direction
    if (shift=="Right") {
        if (y + 1 >= columns || board[x][y + 1] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        board[x][y] = '.';
        board[x][y+1] = mark;
    }
    else if (shift=="Left") {
        if (y - 1 < 0 || board[x][y - 1] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        board[x][y] = '.';
        board[x][y-1] = mark;
    }
    else if (shift=="Down") {
        if (x + 1 >= rows || board[x + 1][y] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        board[x][y] = '.';
        board[x + 1][y] = mark;
    }
    else if (shift=="Up") {
        if (x - 1 < 0 || board[x - 1][y] != '.' ) {
            cout<<"Choose another Direction."<<endl;
            return false;
        }
        board[x][y] = '.';
        board[x - 1][y] = mark;
    }

    // Sync AI matrix with board
    Matrix1 = board;
    return true;
}

/**
 * @brief Checks if the player has achieved a winning condition in Shift X-O.
 *
 * Win Conditions:
 *  - Any full row of 4 matching pieces
 *  - Any full column of 4 matching pieces
 *  - 3-length diagonal sequences
 *  - 4-length major diagonals
 *
 * @param player The player whose win status is checked.
 * @return true if win detected, otherwise false.
 */
bool X_O_Shift::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    // Check sliding 4-length matches
    auto all_equal_4 = [&](char a, char b, char c, char d) {
        if (a==b && b==c && a!=blank_symbol && a == sym) return true;
        if (b==c && c==d && d!=blank_symbol && b == sym) return true;
        return false;
    };

    // Check simple 3-length diagonal matches
    auto all_equal_3 = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol && a == sym;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if (all_equal_4(board[i][0], board[i][1], board[i][2], board[i][3]) ||
            all_equal_4(board[0][i], board[1][i], board[2][i], board[3][i]))
            return true;
    }

    // 3-length Diagonals (upper)
    if ((all_equal_3(board[2][0], board[1][1], board[0][2]) && board[0][2] == sym) ||
        (all_equal_3(board[3][1], board[2][2], board[1][3]) && board[3][1] == sym))
        return true;

    // 3-length Diagonals (lower)
    if ((all_equal_3(board[1][0], board[2][1], board[3][2]) && board[1][0] == sym) ||
        (all_equal_3(board[0][1], board[1][2], board[2][3]) && board[0][1] == sym))
        return true;

    // Full 4-length diagonals
    if (all_equal_4(board[0][0],board[1][1],board[2][2],board[3][3]) ||
        all_equal_4(board[0][3],board[1][2],board[2][1],board[3][0]))
        return true;

    return false;
}

/**
 * @brief Determines if the game is a draw.
 *
 * A draw happens in Shift X-O when:
 *  - Each player has used all 6 moves (n_moves == 12)
 *  - AND no winning condition exists
 */
bool X_O_Shift::is_draw(Player<char>* player) {
    return (n_moves == 12 && !is_win(player));
}

/**
 * @brief Checks if the game is finished (win or draw).
 */
bool X_O_Shift::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


//----------------------------------------------------------
// X_O_Shift UI Implementation
//----------------------------------------------------------

/**
 * @brief Initializes the Shift X-O UI with a welcome message.
 */
X_O_Shift_UI::X_O_Shift_UI()
    : UI<char>("Weclome to FCAI Shift X-O ", 3) {}

/**
 * @brief Creates a player (Human or Computer) for Shift X-O.
 */
Player<char>* X_O_Shift_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Retrieves the next move from the player.
 *
 * Human player:
 *  - Selects a piece by typing (x, y)
 *  - Selects direction: Right / Left / Up / Down
 *
 * Computer player:
 *  - Scans Matrix1 for its pieces
 *  - Tries all 4 directions
 *  - Picks the first valid shift
 */
Move<char>* X_O_Shift_UI::get_move(Player<char>* player) {
    int x,y;

    // Human input mode
    if (player->get_type() == PlayerType::HUMAN) {
        cout<<"Choose the position of the piece you want to move : ";
        cin>>x>>y;
        cout<<"Select Your Move (Right , Left , Up , Down) ";
        string s;
        cin>>s;
        shift = s;
    }

    // Computer AI mode
    if (player->get_type() == PlayerType::COMPUTER) {
        char sym = player->get_symbol();

        vector<string> dirs = {"Right", "Left", "Down", "Up"};

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                if (Matrix1[i][j] != sym) continue;

                for (auto d : dirs) {
                    int nx = i, ny = j;

                    if (d == "Right")  ny++;
                    if (d == "Left")   ny--;
                    if (d == "Down")   nx++;
                    if (d == "Up")     nx--;

                    if (nx >= 0 && nx < 4 &&
                        ny >= 0 && ny < 4 &&
                        Matrix1[nx][ny] == '.')
                    {
                        shift = d;
                        return new Move<char>(i, j, sym);
                    }
                }
            }
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}
