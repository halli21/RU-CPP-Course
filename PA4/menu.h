#include <vector>

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
    string new_char_options;
    vector<vector<string>> roles;
    void get_roles();
    bool valid_option(string option, int option_len);
    void create_new_character();
    
};