#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>

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
        //vector<string> temp;
        //cout << "tp2 " << tp2 << endl;
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

    map<string, int> creatures_map {};
    map<string, int> eldritch_map {};

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
    line = line + ";" + life[0];
    if (life[1] != life[0]) {
        line = line + "-" + life[1];
    }

    cout << "What is the min strength? ";
    cin >> add;
    strength[0] = add;
    cout << "What is the max strength? ";
    cin >> add;
    strength[1] = add;
    line = line + ";" + strength[0];
    if (strength[1] != strength[0]){
        line = line + "-" + strength[1];
    }

    cout << "What is the min intelligence? ";
    cin >> add;
    intel[0] = add;
    cout << "What is the max intelligence? ";
    cin >> add;
    intel[1] = add;
    line = line + ";" + intel[0];
    if (intel[1] != strength[0]) {
        line = line + "-" + intel[1];
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
    line = line + ";" + fear[0];
    if (fear[1] != fear[0]) {
        line = line + "-" + fear[1];
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
    line = line + ";" + disquiet[0];
    if (disquiet[1] != disquiet[0]) {
        line = line + "-" + disquiet[1];
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
    line = line + ";" + terror[0];
    if (terror[1] != terror[0]) {
        line = line + "-" + terror[1];
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
    line = line + ";" + traumatism[0];
    if (traumatism[1] != traumatism[0]) {
        line = line + "-" + traumatism[1];
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
    enum Choice {person = 1, creature, investigator, eldritchHorror, back};
    const char* convert_enum[] = {stringify( person ),stringify( creature ),stringify( investigator ),stringify( eldritchHorror )};
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
        case person: 
            cout << "create person" << endl;
            line = get_person_info(line);
            save_to_file(file, line);
            break;

        case creature:
            cout << "create creature" << endl;
            line = get_creature_info(line);
            save_to_file(file, line);
            break;

        case investigator:
            cout << "create investigator" << endl;
            line = get_investigator_info(get_person_info(line));
            save_to_file(file, line);
            break;

        case eldritchHorror:
            cout << "create eldritchHorror" << endl;
            line = get_eldritch_info(get_creature_info(line));
            save_to_file(file, line);
            break;

        case back:
            go_back = true;
            break;
        }
    }

    cout << line << endl;

}


int Menu::random_int(int min, int max){
    srand(time(nullptr));

    int randomInt = rand() % (max - min + 1) + min;

    return randomInt;
}

pair<int, int> Menu::getTwoIntsFromString(const string& str){
    size_t dashPos = str.find("-");
    string firstStr = str.substr(0, dashPos);
    string secondStr = str.substr(dashPos + 1);
    int firstInt = stoi(firstStr);
    int secondInt = stoi(secondStr);

    return make_pair(firstInt, secondInt);
}


string Menu::create_random_entry(vector<string> character){
    string entry;

    string type = character[0];
    string name = character[1];

    entry += type + ";" + name;

    pair<int, int> life = getTwoIntsFromString(character[2]);
    pair<int, int> strength = getTwoIntsFromString(character[3]);
    pair<int, int> intel = getTwoIntsFromString(character[4]);

    int randomLife = random_int(life.first, life.second);
    int randomStrength = random_int(strength.first, strength.second);
    int randomIntel = random_int(intel.first, intel.second);


    entry += ";" + to_string(randomLife) + ";" + to_string(randomStrength) + ";" + to_string(randomIntel);


    if (type == "Person" || type == "Investigator"){
        string gender = character[5];
        pair<int, int> fear = getTwoIntsFromString(character[6]);
        int randomFear = random_int(fear.first, fear.second);

        entry += ";" + gender + ";" + to_string(randomFear);
    }

    else if (type == "Creature" || type == "Eldritch Horror"){
        string natural = character[5];
        
        pair<int, int> disquiet = getTwoIntsFromString(character[6]);
        int randomDisquiet = random_int(disquiet.first, disquiet.second);

        entry += ";" + natural + ";" + to_string(randomDisquiet);
    }

    if (type == "Investigator"){
        pair<int, int> terror = getTwoIntsFromString(character[7]);
        int randomTerror = random_int(terror.first, terror.second);

        entry += ";" + to_string(randomTerror);
    }

    else if (type == "Eldritch Horror"){
        pair<int, int> traumatism = getTwoIntsFromString(character[7]);
        int randomTraumatism = random_int(traumatism.first, traumatism.second);

        entry += ";" + to_string(randomTraumatism);
    }

    return entry;
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

    string entry = create_random_entry(character);
    save_to_file("characters.txt", entry);
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