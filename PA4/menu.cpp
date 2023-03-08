#include <iostream>
#include <cctype>

#include "menu.h"

using namespace std;


Menu::Menu(){
    options = "1) Create\n2) Edit\n3) View\n4) Quit\n";
}

bool Menu::valid_option(string option){
    if (1 == option.length() && (option[0] >= '1' && option[0] <= '4')) {
        return true;
    }
    return false;
}

int Menu::get_action(){
    cout << options << endl;
    string option;
    cout << "Enter option: ";
    cin >> option;
    
    if (valid_option(option) == true){
        return stoi(option);
    }
    return 0;
}