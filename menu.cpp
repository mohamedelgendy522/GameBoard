#include <iostream>
#include <string>   
#include <vector>   
#include <memory>   

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "Four_In_Row.h"
#include "Word_tic_tac_toe.h"
#include "Infinity_Tic_Tac_Toe.h"
#include "Shift XO.h"
#include "Misere_Tic_Tac_Toe.h"
#include "SUS.h"
using namespace std;
int main() {
    cout << "==================================\n"
         << "          Games Menu\n"
         << "==================================\n"
         << "1. Tic-Tac-Toe\n"
         << "2. Numerical Tic-Tac-Toe\n"
         << "3. Word Tic-Tac-Toe\n"
         << "4. Four-In-A-Row\n"
         << "5. Infinity Tic-Tac-Toe\n"
         << "6. 4 x 4 Tic-Tac-Toe\n"
         << "7. Misere Tic-Tac-Toe\n"
         << "8. SUS\n"
         << "----------------------------------\n"
         << "Enter the number of the game u want to play: ";
    int choice;
    cin >> choice;
    cout << "///////////////////////////////////////////////////////////////////////////////////////////////////////////\n";

    switch (choice) {
    case 1:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new XO_UI();

        Board<char>* xo_board = new X_O_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> x_o_game(xo_board, players, game_ui);

        x_o_game.run();
        
        delete xo_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
        
        delete[] players;

        break;
    }
    case 2:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<int>* game_ui = new Numerical_UI();

        Board<int>* nxo_board = new Numerical_Board();

        Player<int>** players = game_ui->setup_players();

        GameManager<int> Numerical_game(nxo_board, players, game_ui);

        Numerical_game.run();

        delete nxo_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 3:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Word_UI();

        Board<char>* word_board = new Word_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> Word_game(word_board, players, game_ui);

        Word_game.run();

        delete word_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 4:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new FourInRow_UI();

        Board<char>* four_in_row_board = new FourInRow_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> four_in_row_game(four_in_row_board, players, game_ui);

        four_in_row_game.run();

        delete four_in_row_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 5:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Infinity_UI();

        Board<char>* infinity_board = new Infinity_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> infinity_game(infinity_board, players, game_ui);

        infinity_game.run();

        delete infinity_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 6:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new X_O_Shift_UI();

        Board<char>* xo_shift_board = new X_O_Shift_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> xo_shift_game(xo_shift_board, players, game_ui);

        xo_shift_game.run();

        delete xo_shift_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 7:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Inverse_X_O_UI();

        Board<char>* inverse_xo_board = new Inverse_X_O_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> inverse_xo_game(inverse_xo_board, players, game_ui);

        inverse_xo_game.run();

        delete inverse_xo_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
        case 8:
{
    srand(static_cast<unsigned int>(time(0)));

    UI<char>* game_ui = new SUS_UI();

    Board<char>* sus_board = new SUS_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> SUS_game(sus_board, players, game_ui);

    SUS_game.run();

    delete sus_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    delete[] players;

    break;
}
    default:
        cout << "Invalid choice.\n";
        break;
    }
    return 0;
}
