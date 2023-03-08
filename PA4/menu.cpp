#include <iostream>
#include <cctype>

#include "menu.h"

using namespace std;


Menu::Menu(){
    options = "1) Create\n2) Edit\n3) View\n4) Quit\n";
}

bool Menu::valid_option(string option){
    for (char c : option) {
        if (!isdigit(c)) {
            return false;
        }
    }
    if ((int)option[0] < 1 || (int)option[0] > 4){
        return false;
    }
    return true;
}

int Menu::get_action(){
    cout << options << endl;
    string option;
    cout << "Enter option: ";
    cin >> option;
    
    if (valid_option(option) == true){
        return (int)option[0];
    }
    return 0;
}