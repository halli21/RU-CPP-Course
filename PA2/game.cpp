#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>  /* srand, rand */
#include <time.h>
#include "game.h"

using namespace std;

Game::Game() {
    word_file = "words.txt";
    word = "";
}



void Game::get_random_word() {
    char my_string[128];

    int rand_line;

    srand ( time(NULL) );

    rand_line = rand() % 5 + 0;
    std::cout << "Random line nr. : " << rand_line << std::endl;

    ifstream fin;
    fin.open("words.txt");


    for (int i = rand_line; i > 0; i--) {
        fin >> my_string;
        word = my_string;
    }

    fin.close();

}