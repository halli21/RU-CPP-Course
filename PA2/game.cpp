#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>  /* srand, rand */
#include <time.h>
#include "game.h"
#include <chrono>



using namespace std;

Game::Game() {
    strcpy(word_file, "words.txt");
    strcpy(original_word, "");
    strcpy(scrambled_word, "");
    strcpy(hint_word, "");

}

char* Game::get_original_word() {
    return original_word;
}

char* Game::get_scrambled_word() {
    return scrambled_word;
}


void Game::get_random_word() {
    DynamicArray arr;
    char word[45];
    const int delimiter = 45;
    int rand_line;


    ifstream fin;
    fin.open(word_file);

    while (fin.getline(word, delimiter)) {
        arr.push_back(word);
    }

    int arr_size = arr.get_size();

    srand (time(NULL));
    rand_line = rand() % arr_size + 1;

    strcpy(original_word, arr[rand_line]);

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


void Game::get_dashes() {
    int size = strlen(original_word);

    for (int i = 0; i < size; i++) {
        hint_word[i] = '-';
    }
    
}

void Game::get_hint() {
    int size = strlen(original_word);
    int rand_index;
    int hint = false;

    while (!hint)
    {
        srand (time(NULL));
        rand_index = rand() % size + 0;

        if (hint_word[rand_index] == '-'){
            hint_word[rand_index] =  original_word[rand_index];
            hint = true;
        }
    } 

}

char* Game::get_hint_word() {
    return hint_word;
}


void Game::play_game() {

    char guess[45];
    char hint[45];
    hint[0] = 'h';
    double points = 10.0;
    bool got_hint = false;

    // reikna score
    int score = 0;
    int right_answer = 0;

    while (points > 0) {

        bool correct = false;

        get_random_word();
        scramble_word();
        get_dashes();
    
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        while (!correct) {

            interval();

            std::cout << "Your scrambled word is " << "'" << get_scrambled_word() << "'\n" << std::endl;

            std::cout << "Press h to get a hint: " << get_hint_word() << "'\n" << std::endl;

            cout << "What do you think the word is? ";

            std::cin >> guess;


            if (strcmp(guess, hint) == 0) {
                points -= 1;
                score -= 25;
                get_hint();
                got_hint = true;

            }
            else if (strcmp(guess, get_original_word()) != 0) {
                cout << "\n\nWrong, try again!\n";
                points -= 0.25;

            } 
            else {
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                double seconds = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() / 1000000000.00;

                std::cout << "\n\nCorrect!\n" << std::endl;
                std::cout << "You were: " << seconds << " seconds"<< std::endl;

                correct = true;

                int correct_score = get_score(seconds);
                score += correct_score;

                std::cout << score << std::endl;
            }
        }
    }   
}

int Game::get_score(double sec) {
    int score = 100;

    if (sec <= 20) {
        score += 100;
    } 
    else if ((20 < sec) && (sec <= 40)) {
        score += 75;
    }
    else if ((40 < sec) && (sec <= 60)) {
        score += 50;
    }
    else if ((60 < sec) && (sec <= 90)) {
        score += 25;
    }

    return score;
}

void Game::add_score(int score) {
    char initials[3];

    cout << "\nPlease enter your initials (max 3 char): ";
    std::cin >> initials;



}



DynamicArray::DynamicArray() {
    size = 0;
    capacity = 1;
    arr = new char*[capacity];
}


void DynamicArray::push_back(const char* word) {
    if (size == capacity) {
        capacity *= 2;
        char** newArr = new char*[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[size] = new char[strlen(word) + 1];
    strcpy(arr[size], word);
    size++;
}


int DynamicArray::get_size() {
    return size;
}

char* DynamicArray::operator[](int index) const {
    if (index >= size) {
        std::cout << "Index out of range" << std::endl;
        return nullptr;
    }
    return arr[index];
}

DynamicArray::~DynamicArray() {
        for (int i = 0; i < size; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
