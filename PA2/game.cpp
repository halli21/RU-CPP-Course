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

void Game::hint(){
    int size = strlen(original_word);
    int rand_index;

    srand (time(NULL));
    rand_index = rand() % size + 0;

    hint_word[rand_index] =  original_word[rand_index];
     
}

char* Game::get_hint(){
    return hint_word;
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
