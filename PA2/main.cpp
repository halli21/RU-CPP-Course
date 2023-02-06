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
        
        //system("clear");

        char guess[45];
        char hint[45];
        hint[0] = 'h';
        bool end_game = false;

        test.get_random_word();
        test.scramble_word();
        test.get_dashes();
       
        while (!end_game) {

            test.interval();

            std::cout << "Your scrambled word is " << "'" << test.get_scrambled_word() << "'\n" << std::endl;
                

            std::cout << "Press h to get a hint: " << test.get_hint() << "'\n" << std::endl;


            cout << "What do you think the word is? ";

            std::cin >> guess;


            if (strcmp(guess, hint) == 0){
                test.hint();

            }
            else if (strcmp(guess, test.get_original_word()) != 0) {
                char continue_game;

                cout << "\n\nWrong, do you want to guess again (y or n)? ";

                std::cin >> continue_game;

                if (continue_game == 'n') {
                    end_game = true;
                }

            } 
            else {

                std::cout << "\n\nCorrect!\n" << std::endl;
                
                end_game = true;
            }

        }

    }


    return 0;

}