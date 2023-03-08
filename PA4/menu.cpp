#include <iostream>
#include <cctype>

#include "menu.h"

using namespace std;


Menu::Menu(){
    menu_options = "\n1) Create\n2) Edit\n3) View\n4) Quit\n";
    create_options = "\n1) Create new character\n2) Create existing character\n3) Go back\n";
}

bool Menu::valid_option(string option, int option_len){
    char max = option_len + '0';
    if (1 == option.length() && (option[0] >= '1' && option[0] <= max)) {
        return true;
    }
    return false;
}

int Menu::get_action(){
    int option_len = 4;
    cout << menu_options << endl;
    string option;
    cout << "Enter option: ";
    cin >> option;
    
    if (valid_option(option, option_len) == true){
        return stoi(option);
    }
    return 0;
}


void Menu::create_new_character(){
    enum Choice {new_char = 1, existing_char, back};



}


void Menu::create_character_menu(){
    int option_len = 3;
    enum Choice {new_char = 1, existing_char, back};
    
    bool go_back = false;
    while(go_back == false) {
        cout << create_options << endl;
        string option;
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, option_len) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        Choice my_choice = Choice(stoi(option));
        
        switch(my_choice){
        case new_char:
            cout << "create new" << endl;
            break;

        case existing_char:
            cout << "create existing" << endl;
            break;

        case back:
            go_back = true;
            break;
        }
    }
}