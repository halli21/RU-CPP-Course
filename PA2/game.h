using namespace std;


class Game {       
 public:
    Game();

    void get_random_word();

    void scramble_word();

    char* get_original_word();

    char* get_scrambled_word();

    void get_main_menu();

    void interval();

    void get_dashes();

    void get_hint();

    char* get_hint_word();

    void play_game();


 private:
    char word_file[10];
    char highscore_file[14];
    char original_word[45];   //lengsta orð ever er 45 stafir
    char scrambled_word[45];
    char hint_word[45];


    int get_score(double, double);

    void add_score(int);

};



