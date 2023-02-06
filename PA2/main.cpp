#include <iostream>
#include "game.h"



using namespace std;



int main() {

    char option;

    Game test;

    test.get_main_menu();

    cout << "\nPlease choose an option: ";

    std::cin >> option;

    if (option == '1') {
        test.play_game();
    }


    return 0;

}