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
    void delete_menu();
    void view_menu();
    void switch_roster();

    
    

private:
    string rosterFileName = "characters.txt";;
    string menu_options;
    string create_options;
    string new_char_options;
    string edit_options;
    string delete_options;
    string view_options;
    map<string, int> creatures_map;
    map<string, int> eldritch_map;
    vector<vector<string>> roles;
    list<Character*> characters;


    void get_roles();
    void get_characters();
    void available_roles();
    void all_roles();
    void all_characters();
    void all_investigators();
    bool valid_option(string option, int option_len);
    void create_new_character();
    void create_existing_character();
    void edit_role();
    void edit_character();
    void delete_role();
    void view_roles();
    void view_characters();
    void view_single();
    void save_roles();
    void save_characters();
    int random_int(int min, int max);
    pair<int, int> getTwoIntsFromString(const string& str);
    string create_random_entry(vector<string> character);
    string get_being_info(string line);
    string get_person_info(string line);
    string get_creature_info(string line);
    string get_investigator_info(string line);
    string get_eldritch_info(string line);
    void save_to_file(string filename, string line);
    void roles_to_file(string filename);
    void chars_to_file(string filename);
    void invs_to_file(string filename);
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