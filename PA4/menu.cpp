#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

#include "menu.h"

#define stringify( name ) #name

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

void Menu::get_characters(){
    fstream charsFile;
    charsFile.open("characters.txt",ios::in);
    string tp2;
    while(getline(charsFile, tp2)){ 
        vector<string> temp;
        cout << "tp2 " << tp2 << endl;
        stringstream ss(tp2);
        while ( ss.good() ) {
            string substr;
            getline( ss, substr, ';' );
            temp.push_back( substr );
        }

        characters.push_back(temp);
    }
    charsFile.close();
}


Menu::Menu(){
    get_roles();
    get_characters();

    menu_options = "\n1) Create\n2) Edit\n3) View\n4) Quit\n";
    create_options = "\n1) Create new character\n2) Create existing character\n3) Go back\n";
    new_char_options = "\n1) Person\n2) Creature\n3) Investigator\n4) Eldritch Horror\n5) Go back\n";
    edit_options = "\n1) Edit role\n2) Edit character\n3) Go Back\n";
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


int Menu::valid_value(int value, int min, int max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    else {
        return value;
    }
}


string Menu::get_being_info(string line) {
    string add;
    string type;
    string life[2];
    string strength[2];
    string intel[2];

    cout << "What is the name of the role/species? ";
    cin >> add;
    line = line + ";" + add;

    cout << "What is the min life? ";
    cin >> add;
    life[0] = add;
    cout << "What is the max life? ";
    cin >> add;
    life[1] = add;
    line = line + ";" + to_string(valid_value(stoi(life[0]), 0, 10));
    if (life[1] != life[0]) {
        if (life[1] > to_string(valid_value(stoi(life[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(life[1]), stoi(life[0]), 10));
    }

    cout << "What is the min strength? ";
    cin >> add;
    strength[0] = add;
    cout << "What is the max strength? ";
    cin >> add;
    strength[1] = add;
    line = line + ";" + to_string(valid_value(stoi(strength[0]), 0, 10));
    if (strength[1] != strength[0]) {
        if (strength[1] > to_string(valid_value(stoi(strength[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(strength[1]), stoi(strength[0]), 10));
    }

    cout << "What is the min intelligence? ";
    cin >> add;
    intel[0] = add;
    cout << "What is the max intelligence? ";
    cin >> add;
    intel[1] = add;
    line = line + ";" + to_string(valid_value(stoi(intel[0]), 0, 10));
    if (intel[1] != intel[0]) {
        if (intel[1] > to_string(valid_value(stoi(intel[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(intel[1]), stoi(intel[0]), 10));
    }


    cout << "being " << line << endl;

    return line;
}


string Menu::get_person_info(string line) {
    string add;
    string fear[2];

    cout << "What gender is this person? ";
    cin >> add;
    line = line + ";" + add;

    cout << "What is the min fear? ";
    cin >> add;
    fear[0] = add;
    cout << "What is the max fear? ";
    cin >> add;
    fear[1] = add;
    line = line + ";" + to_string(valid_value(stoi(fear[0]), 0, 10));
    if (fear[1] != fear[0]) {
        if (fear[1] > to_string(valid_value(stoi(fear[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(fear[1]), stoi(fear[0]), 10));
    }

    cout << "person " << line << endl;
    return line;
}


string Menu::get_creature_info(string line) {
    string add;
    string disquiet[2];

    cout << "Is the creature natural (true/false)? ";
    cin >> add;
    line = line + ";" + add;

    cout << "What is the min disquiet? ";
    cin >> add;
    disquiet[0] = add;
    cout << "What is the max disquiet? ";
    cin >> add;
    disquiet[1] = add;
    line = line + ";" + to_string(valid_value(stoi(disquiet[0]), 0, 10));
    if (disquiet[1] != disquiet[0]) {
        if (disquiet[1] > to_string(valid_value(stoi(disquiet[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(disquiet[1]), stoi(disquiet[0]), 10));
    }

    cout << "creature " << line << endl;
    return line;
}


string Menu::get_investigator_info(string line) {
    string add;
    string terror[2];

    cout << "What is the min terror? ";
    cin >> add;
    terror[0] = add;
    cout << "What is the max terror? ";
    cin >> add;
    terror[1] = add;
    line = line + ";" + to_string(valid_value(stoi(terror[0]), 0, 10));
    if (terror[1] != terror[0]) {
        if (terror[1] > to_string(valid_value(stoi(terror[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(terror[1]), stoi(terror[0]), 10));
    }

    cout << "investigator " << line << endl;
    return line;
}

string Menu::get_eldritch_info(string line) {
    string add;
    string traumatism[2];

    cout << "What is the min traumatism? ";
    cin >> add;
    traumatism[0] = add;
    cout << "What is the max traumatism? ";
    cin >> add;
    traumatism[1] = add;
    line = line + ";" + to_string(valid_value(stoi(traumatism[0]), 0, 10));
    if (traumatism[1] != traumatism[0]) {
        if (traumatism[1] > to_string(valid_value(stoi(traumatism[0]), 0, 10)))
            line = line + "-" + to_string(valid_value(stoi(traumatism[1]), stoi(traumatism[0]), 10));
    }

    cout << "eldritch " << line << endl;
    return line;
}


void Menu::save_to_file(string filename, string line) {
    fstream file;
    file.open(filename, ios::app);
    file << line + "\n";
    file.close();
}


void Menu::create_new_character(){
    int option_len = 5;
    enum Choice {Person = 1, Creature, Investigator, EldritchHorror, Back};
    const char* convert_enum[] = {stringify( Person ),stringify( Creature ),stringify( Investigator ),stringify( EldritchHorror )};
    string line;
    string file = "roles.txt";

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
        line = convert_enum[Choice(stoi(option) - 1)];

        line = get_being_info(line);
        
        switch(my_choice){
        case Person: 
            cout << "create person" << endl;
            line = get_person_info(line);
            save_to_file(file, line);
            go_back = true;
            break;

        case Creature:
            cout << "create creature" << endl;
            line = get_creature_info(line);
            save_to_file(file, line);
            go_back = true;
            break;

        case Investigator:
            cout << "create investigator" << endl;
            line = get_investigator_info(get_person_info(line));
            save_to_file(file, line);
            go_back = true;
            break;

        case EldritchHorror:
            cout << "create eldritchHorror" << endl;
            line = get_eldritch_info(get_creature_info(line));
            save_to_file(file, line);
            go_back = true;
            break;

        case Back:
            go_back = true;
            break;
        }
    }

    cout << line << endl;

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


void Menu::edit_menu(){
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