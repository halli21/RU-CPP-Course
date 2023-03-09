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
    void edit_menu();
    
    

private:
    string menu_options;
    string create_options;
    string new_char_options;
    string edit_options;
    vector<vector<string>> roles;
    vector<vector<string>> characters;
    void get_roles();
    void get_characters();
    bool valid_option(string option, int option_len);
    void create_new_character();
    void create_existing_character();
    string get_being_info(string line);
    string get_person_info(string line);
    string get_creature_info(string line);
    string get_investigator_info(string line);
    string get_eldritch_info(string line);
    void save_to_file(string filename, string line);
    int valid_value(int value, int min, int max);
    
};