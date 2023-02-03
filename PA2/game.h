using namespace std;


class Game {       
  public:
    Game();
    string word_file;       // Þurfum að breyta megum ekki nota string        
    string original_word;
    string scrambled_word;

    void get_random_word();

    void scramble_word();
};
