#include <iostream>
#include <string>   
#include <vector>   
#include <memory>   

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "SUS.h"
#include "Four_In_Row.h"
#include "Word_tic_tac_toe.h"
#include "Big_XO_Tic_Tac_Toe.h"
#include "Infinity.h"
#include "Shift_X_O.h"
#include "Misere_Tic_Tac_Toe.h"
#include "Diamond_Tic_Tac_Toe.h"
#include "Obstacles_Tic_Tac_Toe.h"
#include "Pyramid.h"
#include "Memory_Tic_Tac_Toe.h"
#include "Ultimate.h"
using namespace std;
int main() {
    cout << "==================================\n"
        << "          Games Menu\n"
        << "==================================\n"
        << " 1. Tic-Tac-Toe\n"
        << " 2. Numerical Tic-Tac-Toe\n"
        << " 3. Word Tic-Tac-Toe\n"
        << " 4. Four-In-A-Row\n"
        << " 5. 5 x 5 Tic-Tac-Toe\n"
        << " 6. Infinity Tic-Tac-Toe\n"
        << " 7. 4 x 4 Tic-Tac-Toe\n"
        << " 8. Misere Tic-Tac-Toe\n"
        << " 9. SUS\n"
        << "10. Diamond Tic-Tac-Toe\n"
        << "11. Obstacles Tic-Tac-Toe\n"
        << "12. Pyramid Tic-Tac-Toe\n"
        << "13. Memory Tic-Tac-Toe\n"
        << "14. Ultimate Tic-Tac-Toe\n"
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

        UI<char>* game_ui = new Big_XO_UI();

        Board<char>* big_xo_board = new Big_XO_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> big_xo_game(big_xo_board, players, game_ui);

        big_xo_game.run();

        delete big_xo_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 6:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new InfinityGame_UI();

        Board<char>* infinity_board = new InfinityGame_Board();

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
    case 7:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new X_O_Shift_UI();

        Board<char>* xo_shift_board = new X_O_Shift();

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
    case 8:
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
    case 9:
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
        case 10:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Diamond_X_O_UI();

        Board<char>* diamond_xo_board = new Diamond_X_O_Board();

        Player<char>** players = game_ui->setup_players();


        players[0]->set_board_ptr(diamond_xo_board);
        players[1]->set_board_ptr(diamond_xo_board);


        Diamond_X_O_Board* specific_board = dynamic_cast<Diamond_X_O_Board*>(diamond_xo_board);
        if (specific_board != nullptr) {

            specific_board->set_players(players[1], players[0]);
        }


        GameManager<char> diamondXO_game(diamond_xo_board, players, game_ui);

        diamondXO_game.run();

        delete diamond_xo_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;
        delete game_ui;

        break;
    }
    case 11:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Obstacles_XO_UI();

        Board<char>* obstacles_xo_board = new Obstacles_XO_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> obstacles_xo_game(obstacles_xo_board, players, game_ui);

        obstacles_xo_game.run();

        delete obstacles_xo_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 12:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Pyramid_UI();

        Board<char>* pyramid_board = new Pyramid();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> pyramid_game(pyramid_board, players, game_ui);

        pyramid_game.run();

        delete pyramid_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 13:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Memory_X_O_UI();

        Board<char>* memory_board = new Memory_Board();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> memory_game(memory_board, players, game_ui);

        memory_game.run();

        delete memory_board;

        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        delete[] players;

        break;
    }
    case 14:
    {
        srand(static_cast<unsigned int>(time(0)));

        UI<char>* game_ui = new Ultimate_UI();

        Board<char>* ultimate_board = new Ultimate();

        Player<char>** players = game_ui->setup_players();

        GameManager<char> ultimate_game(ultimate_board, players, game_ui);

        ultimate_game.run();

        delete ultimate_board;

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
