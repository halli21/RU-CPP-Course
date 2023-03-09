#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <time.h>

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

template<class T>
void Menu::add_being_attributes(T& character, vector<string> attributes){
    character->type.edit_life(stoi(attributes[3]));
    character->type.edit_strength(stoi(attributes[4]));
    character->type.edit_intelligence(stoi(attributes[5]));
}

template<class T>
void Menu::add_person_attributes(T& character, vector<string> attributes){
    character->type.edit_gender(attributes[6]);
    character->type.edit_fear(stoi(attributes[7]));
}

template<class T>
void Menu::add_creature_attributes(T& character, vector<string> attributes){
    if (attributes[6] == "true") {
        character->type.edit_natural(true);
    }
    else {
        character->type.edit_natural(false);
    }
    character->type.edit_disquiet(stoi(attributes[7]));
}

template<class T>
void Menu::add_investigator_attributes(T& character, vector<string> attributes){
    character->type.edit_terror(stoi(attributes[8]));
  
}

template<class T>
void Menu::add_eldritch_attributes(T& character, vector<string> attributes){
    character->type.edit_traumatism(stoi(attributes[8]));
}


void Menu::get_characters(){
    fstream charsFile;
    charsFile.open("characters.txt",ios::in);
    string tp;
    while(getline(charsFile, tp)){ 
        vector<string> attributes;
        //cout << "tp2 " << tp2 << endl;
        stringstream ss(tp);
        while ( ss.good() ) {
            string substr;
            getline( ss, substr, ';' );
            attributes.push_back( substr );
        }

        string type = attributes[0];

        if (type == "Person"){
            Role<Person> *character = new Role<Person>;
            character->change_name(attributes[2]);
            add_being_attributes(character, attributes);
            add_person_attributes(character, attributes);   
            characters.push_back(character);        
        }
        else if (type == "Creature"){
            Species<Creature> *character = new Species<Creature>;

            size_t lastSpaceIndex = attributes[2].rfind(' ');

            if (lastSpaceIndex != string::npos){
                string name = attributes[2].substr(0, lastSpaceIndex);
                string status = attributes[2].substr(lastSpaceIndex + 1);

                if (creatures_map.count(name) == 0){
                    creatures_map[name] = 0;
                }
                if (status == "boss") {
                    creatures_map[attributes[2]] = 1;
                }
                creatures_map[name] += 1;
            }
        
            
            character->change_name(attributes[2]);
            add_being_attributes(character, attributes);
            add_creature_attributes(character, attributes);
            characters.push_back(character);
        }
        else if (type == "Investigator"){
            Role<Investigator> *character = new Role<Investigator>;
            character->change_name(attributes[2]);
            add_being_attributes(character, attributes);
            add_person_attributes(character, attributes);
            add_investigator_attributes(character, attributes);
            characters.push_back(character);
       
        }
        else if (type == "Eldritch Horror"){
            Species<EldritchHorror> *character = new Species<EldritchHorror>;

            size_t lastSpaceIndex = attributes[2].rfind(' ');

            if (lastSpaceIndex != string::npos){
                string name = attributes[2].substr(0, lastSpaceIndex);
                string status = attributes[2].substr(lastSpaceIndex + 1);

                if (eldritch_map.count(name) == 0){
                    eldritch_map[name] = 0;
                }
                if (status == "boss") {
                    eldritch_map[attributes[2]] = 1;
                }
                eldritch_map[name] += 1;
            }
            character->change_name(attributes[2]);
            add_being_attributes(character, attributes);
            add_creature_attributes(character, attributes);
            add_eldritch_attributes(character, attributes);
            characters.push_back(character);
        }

    }
    charsFile.close();
}


Menu::Menu(){
    get_roles();
    get_characters();

    //map<string, int> creatures_map {};
    //map<string, int> eldritch_map {};

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
    line = line + ";" + to_string(valid_value(stoi(terror[0]), 0, 3));
    if (terror[1] != terror[0]) {
        if (terror[1] > to_string(valid_value(stoi(terror[0]), 0, 3)))
            line = line + "-" + to_string(valid_value(stoi(terror[1]), stoi(terror[0]), 3));
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
    line = line + ";" + to_string(valid_value(stoi(traumatism[0]), 0, 3));
    if (traumatism[1] != traumatism[0]) {
        if (traumatism[1] > to_string(valid_value(stoi(traumatism[0]), 0, 3)))
            line = line + "-" + to_string(valid_value(stoi(traumatism[1]), stoi(traumatism[0]), 3));
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


void Menu::save_roles() {
    string data;

    for (int i = 0; i < roles.size(); i++) {
        string line;
        for (int x = 0; x < roles[i].size(); x++) {
            if (x == 0) 
                line = line + roles[i][x];
            else 
                line = line + ";" + roles[i][x];
        }
        cout << "line " << line << endl;
        line = line + "\n";
        data = data + line;
    }

    cout << "\nData " << data << endl;

    fstream file;
    file.open("roles.txt", ios::out | ios::trunc);
    file << data;
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


void Menu::available_roles(){
    cout << "\n\n----Here are the roles available----" << endl;

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
}

void Menu::create_existing_character(){

    available_roles();

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

//------------------------------ Edit ----------------------------------

void Menu::edit_role(){
    available_roles();

    vector<string> role;
    string option;

    while(true) {
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, roles.size() + 1) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        if (stoi(option) == roles.size() + 1){
            return;
        }

        role = roles[stoi(option) - 1];
        break;
    }

    string type = role[0];

    cout << "\n\n----Here are the stats available for editing----" << endl;

    cout << "1) Name\n2) Life\n3) Strength\n4) Intelligence" << endl;

    if (type == "Person" || type == "Investigator") {
        cout << "5) Gender\n6) Fear" << endl;
    }
    else if (type == "Creature" || type == "EldritchHorror") {
        cout << "5) Natural\n6) Disquiet" << endl;
    }
    if (type == "Investigator") {
        cout << "7) Terror" << endl;
    }
    else if (type == "EldritchHorror") {
        cout << "7) Traumatism" << endl;
    }

    cout << "\n" << role.size() + 1 << ") Go back\n " << endl;
    string stat_option;

    while(true) {
        cout << "Enter option: ";
        cin >> stat_option;

        if (valid_option(stat_option, role.size() + 1) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        if (stoi(stat_option) == role.size() + 1){
            return;
        }

        break;
    }

    if (stoi(stat_option) == 7) {
        if (type == "Investigator") {
            string terror[2];

            cout << "What is the min terror? ";
            cin >> terror[0];
            cout << "What is the max terror? ";
            cin >> terror[1];
            role[7] = to_string(valid_value(stoi(terror[0]), 0, 3));
            if (terror[1] != terror[0]) {
                if (terror[1] > to_string(valid_value(stoi(terror[0]), 0, 3)))
                    role[7] = role[7] + "-" + to_string(valid_value(stoi(terror[1]), stoi(terror[0]), 3));
            }
        }
        else if (type == "EldritchHorror") {
            string traumatism[2];

            cout << "What is the min traumatism? ";
            cin >> traumatism[0];
            cout << "What is the max traumatism? ";
            cin >> traumatism[1];
            role[7] = to_string(valid_value(stoi(traumatism[0]), 0, 3));
            if (traumatism[1] != traumatism[0]) {
                if (traumatism[1] > to_string(valid_value(stoi(traumatism[0]), 0, 3)))
                    role[7] = role[7] + "-" + to_string(valid_value(stoi(traumatism[1]), stoi(traumatism[0]), 3));
            }
        }
    }
    else if (stoi(stat_option) == 6 || (stoi(stat_option) >= 2 & stoi(stat_option) <= 4)) {
        if (type == "Person" || type == "Investigator") {
            string stats[2];

            cout << "What is the min? ";
            cin >> stats[0];
            cout << "What is the max? ";
            cin >> stats[1];
            role[stoi(stat_option)] = to_string(valid_value(stoi(stats[0]), 0, 10));
            if (stats[1] != stats[0]) {
                if (stats[1] > to_string(valid_value(stoi(stats[0]), 0, 10)))
                    role[stoi(stat_option)] = role[stoi(stat_option)] + "-" + to_string(valid_value(stoi(stats[1]), stoi(stats[0]), 10));
            }
        }
        else if (type == "Creature" || type == "EldritchHorror") {
            string stats[2];

            cout << "What is the min? ";
            cin >> stats[0];
            cout << "What is the max? ";
            cin >> stats[1];
            role[stoi(stat_option)] = to_string(valid_value(stoi(stats[0]), 0, 10));
            if (stats[1] != stats[0]) {
                if (stats[1] > to_string(valid_value(stoi(stats[0]), 0, 10)))
                    role[stoi(stat_option)] = role[stoi(stat_option)] + "-" + to_string(valid_value(stoi(stats[1]), stoi(stats[0]), 10));
            }
        }
    }
    else {
        string stats;

        cout << "What is the new value? ";
        cin >> stats;
        if (type == "Creature" || type == "EldritchHorror") {
            if (stat_option == "5") {
                while (true) {
                    if (stats == "true" || stats == "false") 
                        break;
                    else {
                        cout << "Invalid input! Has to be 'true' or 'false'" << endl;
                        cout << "What is the new value ('true' or 'false')?";
                        cin >> stats;
                    }
                }
            }
        }
        role[stoi(stat_option)] = stats;
    }

    roles[stoi(option) - 1] = role;

    save_roles();

    /*available_roles();

    for (int i = 0; i < role.size(); i++) {
        cout << role[i] << endl;
    }*/
}


void Menu::edit_character(){
    cout << "Edit character\n";
}


void Menu::edit_menu(){
    int option_len = 3;
    enum Choice {role = 1, character, back};
    
    bool go_back = false;
    while(go_back == false) {
        cout << edit_options << endl;
        string option;
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, option_len) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        Choice my_choice = Choice(stoi(option));
        
        switch(my_choice){
        case role:
            edit_role();
            break;

        case character:
            edit_character();
            break;

        case back:
            go_back = true;
            break;
        }
    }
}