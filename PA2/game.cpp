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
    strcpy(highscore_file, "highscore.txt");
    memset(original_word, 0, sizeof(original_word));
    memset(scrambled_word, 0, sizeof(scrambled_word));
    memset(hint_word, 0, sizeof(hint_word));
    get_words_arr();
    get_highscore_arr();



}

 void Game::get_words_arr() {
    char word[45];
    const int max = 45;

    ifstream fin;
    fin.open(word_file);

    while (fin.getline(word, max)) {
        words_arr.push_back(word);
    }

    fin.close();
 }



char* Game::get_original_word() {
    return original_word;
}

char* Game::get_scrambled_word() {
    return scrambled_word;
}


void Game::get_random_word() {
    int rand_line;

    int arr_size = words_arr.get_size();


    srand (time(NULL));
    rand_line = 0 + rand() % (arr_size - 1);

    if (arr_size == 1) {      // ÞARF EKKI ENDILEGA VERÐUR ALLTAF EH EN VAR AÐ TESTA EH
        strcpy(original_word, words_arr[0]);
    } else {
        strcpy(original_word, words_arr[rand_line]);
    }



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
    std::cout << "\nWelcome to Word jumble\n\n1 - Play\n2 - Highscore table\n3 - Top 5 scores\n0 - Quit" << std::endl;
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
    char hint[2];
    hint[0] = 'h';
    hint[1] = '\0';
    double points = 10.0;
    bool got_hint = false;
    double streak = 1.0;

    // reikna score
    int score = 0;

    while (points > 0) {

        bool correct = false;
        bool hints_done = false;

        reset_words();
        get_random_word();
        scramble_word();
        get_dashes();
    
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        while (!correct) {
            if (points > 0) {

                interval();

                std::cout << "Your scrambled word is " << "'" << get_scrambled_word() << "'\n" << std::endl;

                if (hints_done) {
                    std::cout << "Hmm.. Better think about this: " << get_hint_word() << "\n" << std::endl;
                } else {
                    std::cout << "Press h to get a hint: " << get_hint_word() << "\n" << std::endl;
                }
            

                cout << "What do you think the word is? ";

                std::cin >> guess;


                if (strcmp(guess, hint) == 0 && !hints_done) {
                    points -= 1;
                    score -= 25;
                    get_hint();
                    got_hint = true;
                    if (strcmp(get_hint_word(), get_original_word()) == 0) {
                        hints_done = true;
                    }

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

                    if (!got_hint){
                        streak += 0.2;
                    }
                    else
                    {
                        streak = 1.00;
                        got_hint = true;
                    }
                    

                    int correct_score = get_score(seconds, streak);
                    score += correct_score;

                }
            } else {
                correct = true;

            }
        }
    }
    interval();
    std::cout << "\nGame Over! You ran out of points, your final score is " << score << ".\n" << std::endl;
    add_score(score);    

}

int Game::get_score(double sec, double streak) {
    int score = 100;

    if (sec <= 20) {
        score += 100 * streak;
    } 
    else if ((20 < sec) && (sec <= 40)) {
        score += 75 * streak;
    }
    else if ((40 < sec) && (sec <= 60)) {
        score += 50 * streak;
    }
    else if ((60 < sec) && (sec <= 90)) {
        score += 25 * streak;
    }

    return score;
}


void Game::reset_words() {
    int size = strlen(original_word);

    for (int i = 0; i < size; i++) {
        original_word[i] = '\0';
        scrambled_word[i] = '\0';
        hint_word[i] = '\0';
    }
}




void Game::add_score(int score) {
    bool valid = false;
    char input[45];
    memset(input, 0, sizeof(input));


    while (!valid) {
        cout << "\nPlease enter your initials to save score (3 char): ";
        std::cin >> input;
        if (strlen(input) == 3) {
            valid = true;
            input[3] = '\0';
        }
    }

    ofstream fout;
    fout.open(highscore_file, ios::app);

    fout << input << ' ' << score << std::endl;

    fout.close();

    char sScore[45];
    char empty[45];
    snprintf(sScore, sizeof(sScore), "%d", score);
    empty[0] = ' ';
    strcat(input, empty);
    strcat(input, sScore);

    highscore_arr.push_back(input);

}






void Game::show_highscore() {

    int arr_size = highscore_arr.get_size();

    if (arr_size == 0) {
        get_highscore_arr();

    }

    for (int i = 0; i < highscore_arr.get_size(); i++)
        {
            std::cout << highscore_arr[i] << std::endl;
        }


}




void Game::get_highscore_arr() {
    char highscore[45];
    const int max = 45;

    ifstream fin;
    fin.open(highscore_file);

    while (fin.getline(highscore, max)) {
        highscore_arr.push_back(highscore);
    }

    fin.close();
 }



 void Game::show_top5() {

    if (highscore_arr.get_size() == 0) {
        get_highscore_arr();
    }

    DynamicArray copy_arr = highscore_arr;

    for (int i = 0; i < 5; i++) {
        int highest_i = 0;
        int highest_num = 0;
        for (int j = 0; j < copy_arr.get_size(); j++) {
            int num = atoi(copy_arr[j] + 4);
            
            if (highest_num < num) {
                highest_num = num;
                highest_i = j;
            }
        }
        std::cout << copy_arr[highest_i] << std::endl;
        copy_arr.remove(highest_i);
    }
 }

