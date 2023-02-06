#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>  /* srand, rand */
#include <time.h>
#include "game.h"

using namespace std;

Game::Game() {
    strcpy(word_file, "words.txt");
    strcpy(original_word, "");
    strcpy(scrambled_word, "");
}

char* Game::get_original_word() {
    return original_word;
}

char* Game::get_scrambled_word() {
    return scrambled_word;
}


void Game::get_random_word() {
    char my_string[45];

    int rand_line;

    srand (time(NULL));
    rand_line = rand() % 5 + 1;     // 1 - 5, HARDCODED FOR NOW

    ifstream fin;
    fin.open("words.txt");

    for (int i = rand_line; i > 0; i--) {
        fin >> my_string;
        strcpy(original_word, my_string);
    }

    fin.close();

}

void Game::scramble_word() {
    char word_copy[45];

    strcpy(word_copy, original_word);

    int size = strlen(original_word);

    bool scrambled = false;


    while (!scrambled) {
        for (int i = 0; i < size; i++) {
            srand (time(NULL));
            int j = rand() % size;
            char temp_char = word_copy[i];
            word_copy[i] = word_copy[j];
            word_copy[j] = temp_char;
        }
        if (strcmp(word_copy, original_word) != 0) {    //Securea scrambled orð
            scrambled = true;
        }
    }

    strcpy(scrambled_word, word_copy);

}



void Game::get_main_menu() {
    std::cout << "\nWelcome to Word jumble\n\n1 - Play" << std::endl;

}


void Game::interval() {

    for (int i = 0; i < 100; i++) {
        std::cout << "-";
    }
    std::cout << "\n" << std::endl;
}