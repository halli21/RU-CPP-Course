#include "DynamicArray.h"

class Game {       
 public:
    Game();

    void get_main_menu();

    void play_game();


 private:
    char word_file[10];
    char highscore_file[14];
    char original_word[45];   //lengsta orð ever er 45 stafir
    char scrambled_word[45];
    char hint_word[45];
    DynamicArray words_arr;
   


    void get_words_arr();

    void get_random_word();

    void scramble_word();

    char* get_original_word();

    char* get_scrambled_word();

    void interval();

    void get_dashes();

    void get_hint();

    char* get_hint_word();

    int get_score(double, double);

    void reset_words();

    void add_score(int);

};



