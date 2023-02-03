using namespace std;


class Game {       
 public:
    Game();

    void get_random_word();

    void scramble_word();

    char* get_original_word();

    char* get_scrambled_word();

 private:
    char word_file[10];
    char original_word[45];   //lengsta orð ever er 45 stafir
    char scrambled_word[45];

};
