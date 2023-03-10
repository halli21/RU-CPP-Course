#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>



#include "menu.h"

enum Choice {invalid, create, edit, del, view, roster, quit};


int main() {

    Menu my_menu;
    Choice my_choice;
    
    while (true) {
        int int_choice = my_menu.get_action();
        Choice my_choice = Choice(int_choice);

        switch(my_choice){
        case create:
            my_menu.create_character_menu();
            break;

        case edit:
            my_menu.edit_menu();
            break;

        case del:
            my_menu.delete_menu();
            break;

        case view:
            my_menu.view_menu();
            break;

        case roster:
            my_menu.switch_roster();
            break;

        case quit:
            return 0;
        
        default:
            cout << "Invalid option!\n" << endl;
            break;
        }
    }
        
    return 0;
}
