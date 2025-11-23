#include"Word_tic_tac_toe.h"

#include<iostream>


using namespace std;

int main() {
    Word_UI ui;
    Word_Board board;

    int mode;
    cout << "Choose game mode:\n";
    cout << "1) Player vs Player\n";
    cout << "2) Player vs Computer\n";
    cout << "Enter choice: ";
    cin >> mode;

    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;

    PlayerType t2;

    if (mode == 1) {
        // Player vs Player
        cout << "Enter Player 2 name: ";
        cin >> name2;
        t2 = PlayerType::HUMAN;
    }
    else {
        // Player vs Computer
        name2 = "Computer";
        t2 = PlayerType::COMPUTER;
    }


    Player<char>* p1 = new Player<char>(name1, 'A', PlayerType::HUMAN);
    Player<char>* p2 = new Player<char>(name2, 'B', t2);

    p1->set_board_ptr(&board);
    p2->set_board_ptr(&board);

    Player<char>* current = p1;

    while (!board.game_is_over(current)) {
        ui.display_board(&board);

        Move<char>* move = ui.get_move(current);
        if (!board.update_board(move)) {
            cout << "Invalid move, try again.\n";
            delete move;
            continue;
        }
        delete move;

        if (board.is_win(current)) {
            ui.display_board(&board);
            cout << current->get_name() << " wins!\n";
            break;
        }

        if (board.is_draw(current)) {
            ui.display_board(&board);
            cout << "It's a draw!\n";
            break;
        }


        current = (current == p1) ? p2 : p1;
    }

    delete p1;
    delete p2;



    return 0;
}