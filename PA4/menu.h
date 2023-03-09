#include <vector>
#include <map>
#include <list>

#include "investigator.h"
#include "eldritchHorror.h"
#include "role.cpp"
#include "species.cpp"
#include "character.cpp"


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
    map<string, int> creatures_map;
    map<string, int> eldritch_map;
    vector<vector<string>> roles;
    list<Character*> characters;


    void get_roles();
    void get_characters();
    bool valid_option(string option, int option_len);
    void create_new_character();
    void create_existing_character();
    int random_int(int min, int max);
    pair<int, int> getTwoIntsFromString(const string& str);
    string create_random_entry(vector<string> character);
    string get_being_info(string line);
    string get_person_info(string line);
    string get_creature_info(string line);
    string get_investigator_info(string line);
    string get_eldritch_info(string line);
    void save_to_file(string filename, string line);
    int valid_value(int value, int min, int max);

    template<class T>
    void add_being_attributes(T& character, vector<string> attributes);

    template<class T>
    void add_person_attributes(T& character, vector<string> attributes);

    template<class T>
    void add_creature_attributes(T& character, vector<string> attributes);

    template<class T>
    void add_investigator_attributes(T& character, vector<string> attributes);

    template<class T>
    void add_eldritch_attributes(T& character, vector<string> attributes);
    
};