#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

#include "menu.h"

using namespace std;



void Menu::get_roles(){

    fstream rolesFile;
    rolesFile.open("roles.txt",ios::in);
    string tp;
    while(getline(rolesFile, tp)){ 
        vector<string> temp;
        stringstream ss(tp);
        while ( ss.good() ) {
            string substr;
            getline( ss, substr, ';' );
            temp.push_back( substr );
        }

        roles.push_back(temp);
    }
    rolesFile.close();
}


Menu::Menu(){
    get_roles();

    menu_options = "\n1) Create\n2) Edit\n3) View\n4) Quit\n";
    create_options = "\n1) Create new character\n2) Create existing character\n3) Go back\n";
    new_char_options = "\n1) Person\n2) Creature\n3) Investigator\n4) Eldritch Horror\n5) Go back\n";
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
    int option_len = 5;
    enum Choice {person = 1, creature, investigator, eldritchHorror, back};

    bool go_back = false;
    while(go_back == false) {
        cout << "\nWhich category is you character?";
        cout << new_char_options << endl;
        string option;
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, option_len) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        Choice my_choice = Choice(stoi(option));
        
        switch(my_choice){
        case person: 
            cout << "create person" << endl;
            break;

        case creature:
            cout << "create creature" << endl;
            break;

        case investigator:
            cout << "create investigator" << endl;
            break;

        case eldritchHorror:
            cout << "create eldritchHorror" << endl;
            break;

        case back:
            go_back = true;
            break;
        }
    }
    /*

    string line;
    string add;
    string type;
    string life[2];
    string strength[2];
    string intel[2];

    cout << "\nWhat type of creature is it? ";
    cin >> type;
    line = type;
    
    cout << "What is the name of the role/species? ";
    cin >> add;
    line = line + ";" + add;

    cout << "What is the min life? ";
    cin >> add;
    life[0] = add;
    cout << "What is the max life? ";
    cin >> add;
    life[1] = add;
    line = line + ";" + "[" + life[0] + "," + life[1] + "]";

    cout << "What is the min strength? ";
    cin >> add;
    strength[0] = add;
    cout << "What is the max strength? ";
    cin >> add;
    strength[1] = add;
    line = line + ";" + "[" + strength[0] + "," + strength[1] + "]";

    cout << "What is the min intelligence? ";
    cin >> add;
    intel[0] = add;
    cout << "What is the max intelligence? ";
    cin >> add;
    intel[1] = add;
    line = line + ";" + "[" + intel[0] + "," + intel[1] + "]";

    fstream rolesFile;
    rolesFile.open("roles.txt", ios::app);
    rolesFile << line + "\n";
    rolesFile.close();

    cout << line << endl;

    */

}


void Menu::create_existing_character(){

    cout << "\n\n----Here are the characters available----" << endl;

    for (int i = 0; i < roles.size(); i++){
     
        cout << "\n" << i + 1 << ") " << roles[i][1] << endl;
        cout << " - " << roles[i][0] << endl;
        cout << " - Life: " << roles[i][2] << endl;
        cout << " - Strength: " << roles[i][3] << endl;
        cout << " - Intelligence: " << roles[i][4] << endl;

        if (roles[i][0] == "Person" || roles[i][0] == "Investigator"){
            cout << " - " << roles[i][5] << endl;
            cout << " - Fear: " << roles[i][6] << endl;
        }
        else if (roles[i][0] == "Creature" || roles[i][0] == "Eldritch Horror"){
            if (roles[i][5] == "true"){
                cout << " - Natural " << endl;
            }
            else {
                cout << " - Unnatural " << endl;
            }
            cout << " - Disquiet: " << roles[i][6] << endl;
        }

        if (roles[i][0] == "Investigator"){
            cout << " - Terror: " << roles[i][7] << endl;
        }
        else if (roles[i][0] == "Eldritch Horror"){
            cout << " - Traumatism: " << roles[i][7] << endl;
        }
    }

    cout << "\n" << roles.size() + 1 << ") Go back\n " << endl;


    vector<string> character;
    
    while(true) {
        string option;
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, roles.size() + 1) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        if (stoi(option) == roles.size() + 1){
            return;
        }

        character = roles[stoi(option) - 1];
        break;
    }

    cout << character[1] << endl;


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
            create_new_character();
            break;

        case existing_char:
            create_existing_character();
            break;

        case back:
            go_back = true;
            break;
        }
    }
}