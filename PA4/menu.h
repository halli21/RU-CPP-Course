

#include "eldritchHorror.h"
#include "role.cpp"
#include "species.cpp"


using namespace std;



class Menu{
public:
    Menu();
    int get_action();
    void create_character_menu();
    

private:
    string menu_options;
    string create_options;
    bool valid_option(string option, int option_len);
    void create_new_character();
};