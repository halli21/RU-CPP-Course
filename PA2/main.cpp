#include <iostream>
#include "game.h"



using namespace std;



int main() {

    char option;

    Game test;
    bool playing = true;

    while (playing) {
        test.get_main_menu();

        cout << "\nPlease choose an option: ";

        std::cin >> option;

        if (option == '1') {
            test.play_game();
        } else if (option == '2') {
            cout << endl;
            test.show_highscore();
        } else if (option == '3') {
            cout << endl;
            test.show_top5();
        } else if (option == '0') {
            playing = false;
            break;
        }
    }

    return 0;

}
