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
    roles.clear();
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
    charsFile.open(rosterFileName,ios::in);
    string tp;
    characters.clear();
    while(getline(charsFile, tp)){ 
        vector<string> attributes;
        stringstream ss(tp);
        while ( ss.good() ) {
            string substr;
            getline( ss, substr, ';' );
            attributes.push_back( substr );
        }

        string type = attributes[0];


        if (type == "Person"){
            Role<Person> *character = new Role<Person>;
            character->change_role_name(attributes[1]);
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

                if (status == "boss") {
                    creatures_map[attributes[2]] = 1;
                }
                else if (creatures_map.count(name) == 0){
                    creatures_map[name] = 1;
                }
                else {
                    creatures_map[name] += 1;
                }

            }
                

            character->change_role_name(attributes[1]);
            character->change_name(attributes[2]);
            add_being_attributes(character, attributes);
            add_creature_attributes(character, attributes);
            characters.push_back(character);
        }
        else if (type == "Investigator"){
            Role<Investigator> *character = new Role<Investigator>;
            character->change_role_name(attributes[1]);
            character->change_name(attributes[2]);
            add_being_attributes(character, attributes);
            add_person_attributes(character, attributes);
            add_investigator_attributes(character, attributes);
            characters.push_back(character);
       
        }
        else if (type == "EldritchHorror"){
            Species<EldritchHorror> *character = new Species<EldritchHorror>;

            size_t lastSpaceIndex = attributes[2].rfind(' ');

            if (lastSpaceIndex != string::npos){
                string name = attributes[2].substr(0, lastSpaceIndex);
                string status = attributes[2].substr(lastSpaceIndex + 1);

                if (status == "boss") {
                    eldritch_map[attributes[2]] = 1;
                }
                else if (eldritch_map.count(name) == 0){
                    eldritch_map[name] = 1;
                }
                else {
                    eldritch_map[name] += 1;
                }
            }
            character->change_role_name(attributes[1]);
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

    menu_options = "\n1) Create\n2) Edit\n3) Delete\n4) View\n5) Switch Roster\n6) Quit\n";
    create_options = "\n1) Create new character\n2) Create existing character\n3) Go back\n";
    new_char_options = "\n1) Person\n2) Creature\n3) Investigator\n4) Eldritch Horror\n5) Go back\n";
    edit_options = "\n1) Edit role\n2) Edit character\n3) Go Back\n";
    delete_options = "\n1) Delete a role\n2) Go Back\n";
    view_options = "\n1) View all roles/species\n2) View all characters\n3) View one role/species\n4) Go Back\n";
}

bool Menu::valid_option(string option, int option_len){
    char max = option_len + '0';
    if (1 == option.length() && (option[0] >= '1' && option[0] <= max)) {
        return true;
    }
    return false;
}

int Menu::get_action(){
    int option_len = 6;
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
        line = line + "\n";
        data = data + line;
    }


    fstream file;
    file.open("roles.txt", ios::out | ios::trunc);
    file << data;
    file.close();
}

void Menu::save_characters() {
    string data;

    for (auto character : characters) {
        string line;
        if (auto person = dynamic_cast<Role<Person>*>(character)) {
            line += person->type.get_type() + ";";
            line += person->get_role_name() + ";";
            line += person->get_name() + ";";
            line += to_string(person->type.get_life_stat()) + ";";
            line += to_string(person->type.get_strength_stat()) + ";";
            line += to_string(person->type.get_intelligence_stat()) + ";";
            line += person->type.get_gender() + ";";
            line += to_string(person->type.get_fear_stat());
        }
        else if (auto creature = dynamic_cast<Species<Creature>*>(character)) {
            line += creature->type.get_type() + ";";
            line += creature->get_role_name() + ";";
            line += creature->get_name() + ";";
            line += to_string(creature->type.get_life_stat()) + ";";
            line += to_string(creature->type.get_strength_stat()) + ";";
            line += to_string(creature->type.get_intelligence_stat()) + ";";
            line += creature->type.get_natural() + ";";
            line += to_string(creature->type.get_disquiet_stat());
        }
        else if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            line += investigator->type.get_type() + ";";
            line += investigator->get_role_name() + ";";
            line += investigator->get_name() + ";";
            line += to_string(investigator->type.get_life_stat()) + ";";
            line += to_string(investigator->type.get_strength_stat()) + ";";
            line += to_string(investigator->type.get_intelligence_stat()) + ";";
            line += investigator->type.get_gender() + ";";
            line += to_string(investigator->type.get_fear_stat()) + ";";
            line += to_string(investigator->type.get_terror_stat());
        }
        else if (auto eldritch = dynamic_cast<Species<EldritchHorror>*>(character)) {
            line += eldritch->type.get_type() + ";";
            line += eldritch->get_role_name() + ";";
            line += eldritch->get_name() + ";";
            line += to_string(eldritch->type.get_life_stat()) + ";";

            line += to_string(eldritch->type.get_strength_stat()) + ";";
            line += to_string(eldritch->type.get_intelligence_stat()) + ";";
            line += eldritch->type.get_natural() + ";";
            line += to_string(eldritch->type.get_disquiet_stat()) + ";";
            line += to_string(eldritch->type.get_traumatism_stat());

        }

        cout << line << endl;
        data += line + "\n";
    }

    fstream file;
    file.open(rosterFileName, ios::out | ios::trunc);
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
            line = get_person_info(line);
            save_to_file(file, line);
            go_back = true;
            break;

        case Creature:
            line = get_creature_info(line);
            save_to_file(file, line);
            go_back = true;
            break;

        case Investigator:
            line = get_investigator_info(get_person_info(line));
            save_to_file(file, line);
            go_back = true;
            break;

        case EldritchHorror:
            line = get_eldritch_info(get_creature_info(line));
            save_to_file(file, line);
            go_back = true;
            break;

        case Back:
            go_back = true;
            break;
        }
    }

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
    string role_name = character[1];
    string name;


    if (type == "Person" || type == "Investigator"){
        cout << "Enter name: ";
        cin >> name;
    }
    else if (type == "Creature"){
        if (creatures_map.count(role_name) == 0){
            creatures_map[role_name] = 0;
        }
        else {
            creatures_map[role_name] += 1; 
            name += role_name + " " + to_string(creatures_map[role_name]);
        }
        
    }
    else if (type == "EldritchHorror"){
        if (eldritch_map.count(role_name) == 0){
            eldritch_map[role_name] = 0;
        }
        else {
            eldritch_map[role_name] += 1; 
            name += role_name + to_string(eldritch_map[role_name]);
        }
    }

    entry += type + ";" + role_name + ";" + name;

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

    else if (type == "Creature" || type == "EldritchHorror"){
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

    else if (type == "EldritchHorror"){
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
        else if (roles[i][0] == "Creature" || roles[i][0] == "EldritchHorror"){
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
        else if (roles[i][0] == "EldritchHorror"){
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
    save_to_file(rosterFileName, entry);
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

}



void Menu::edit_character(){

    cout << "\n\n----Which character would you like to edit?----" << endl;

    int i = 1;

    for (auto character : characters) {
        cout << "\n" << i << ")" << endl;
        if (auto person = dynamic_cast<Role<Person>*>(character)) {
            person->print_stats();
        }
        else if (auto creature = dynamic_cast<Species<Creature>*>(character)) {
            creature->print_stats();
        }
        else if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            investigator->print_stats();
        }
        else if (auto eldritch = dynamic_cast<Species<EldritchHorror>*>(character)) {
            eldritch->print_stats();
        }
        i += 1;
    }

    cout << "\n" << characters.size() + 1 << ") Go back\n " << endl;
    string option;

    while(true) {
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, characters.size() + 1) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        if (stoi(option) == characters.size() + 1){
            return;
        }

        break;
    }

    list<Character*>::iterator it = characters.begin();
    advance(it, stoi(option) - 1);

    Character* character = *it;


    string edit_prompt = "\n1) Edit name\n2) Edit stats\n3) Go back\n";
    int edit_prompt_len = 3;

    cout << edit_prompt << endl;

    string edit_option;


    while(true) {
        cout << "Enter option: ";
        cin >> edit_option;

        if (valid_option(edit_option, edit_prompt_len) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        if (stoi(edit_option) == edit_prompt_len){
            return;
        }

        break;
    }


    if (stoi(edit_option) == 1){
        if (auto person = dynamic_cast<Role<Person>*>(character)) {
            person->edit_name();
        }
        else if (auto creature = dynamic_cast<Species<Creature>*>(character)) {
            creature->edit_name();
        }
        else if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            investigator->edit_name();
        }
        else if (auto eldritch = dynamic_cast<Species<EldritchHorror>*>(character)) {
            eldritch->edit_name();
        }
    }
    else {
        if (auto person = dynamic_cast<Role<Person>*>(character)) {
            person->type.edit_person();
        }
        else if (auto creature = dynamic_cast<Species<Creature>*>(character)) {
            creature->type.edit_creature();
        }
        else if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            investigator->type.edit_investigator();
        }
        else if (auto eldritch = dynamic_cast<Species<EldritchHorror>*>(character)) {
            eldritch->type.edit_eldritch();
        }
    }

    save_characters();
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



//------------------------------ Delete ----------------------------------

void Menu::delete_role(){
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

        roles.erase(roles.begin() + stoi(option) - 1);
        //role = roles[stoi(option) - 1];
        break;
    }

    save_roles();
}


void Menu::delete_menu(){
    int option_len = 2;
    enum Choice {role = 1, back};
    
    bool go_back = false;
    while(go_back == false) {
        cout << delete_options << endl;
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
            delete_role();
            go_back = true;
            break;

        case back:
            go_back = true;
            break;
        }
    }
}


//------------------------------ View ----------------------------------

void Menu::all_roles() {
    cout << "\n\n----Here are all the roles----" << endl;

    for (int i = 0; i < roles.size(); i++){
     
        cout << "\n" << roles[i][1] << endl;
        cout << " - " << roles[i][0] << endl;
        cout << " - Life: " << roles[i][2] << endl;
        cout << " - Strength: " << roles[i][3] << endl;
        cout << " - Intelligence: " << roles[i][4] << endl;

        if (roles[i][0] == "Person" || roles[i][0] == "Investigator"){
            cout << " - " << roles[i][5] << endl;
            cout << " - Fear: " << roles[i][6] << endl;
        }
        else if (roles[i][0] == "Creature" || roles[i][0] == "EldritchHorror"){
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
        else if (roles[i][0] == "EldritchHorror"){
            cout << " - Traumatism: " << roles[i][7] << endl;
        }
    }
}


void Menu::roles_to_file(string filename) {
    string data;

    data = "----Here are the roles available----\n";

    for (int i = 0; i < roles.size(); i++){
        string line;

        line += "\n" + roles[i][1] + "\n";
        line += " - " + roles[i][0] + "\n";
        line += " - Life: " + roles[i][2] + "\n";
        line += " - Strength: " + roles[i][3] + "\n";
        line += " - Intelligence: " + roles[i][4] + "\n";

        if (roles[i][0] == "Person" || roles[i][0] == "Investigator"){
            line += " - " + roles[i][5] + "\n";
            line += " - Fear: " + roles[i][6] + "\n";
        }
        else if (roles[i][0] == "Creature" || roles[i][0] == "EldritchHorror"){
            if (roles[i][5] == "true"){
                line += " - Natural \n";
            }
            else {
                line += " - Unnatural \n";
            }
            line += " - Disquiet: " + roles[i][6] + "\n";
        }

        if (roles[i][0] == "Investigator"){
            line += " - Terror: " + roles[i][7] + "\n";
        }
        else if (roles[i][0] == "EldritchHorror"){
            line += " - Traumatism: " + roles[i][7] + "\n";
        }

        data += line;
    }

    fstream file;
    file.open(filename, ios::out | ios::trunc);
    file << data;
    file.close();

}


void Menu::view_roles(){
    int option_len = 3;
    enum Choice {console = 1, file, back};
    
    bool go_back = false;
    while(go_back == false) {
        cout << "\n1) Print to console\n2) Print to file\n3) Go Back\n" << endl;
        string option;
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, option_len) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        Choice my_choice = Choice(stoi(option));
        string filename;
        
        switch(my_choice){
        case console:
            all_roles();
            go_back = true;
            break;
        
        case file:
            cout << "\nWhat should be the name of the file? ";
            cin >> filename;
            roles_to_file(filename);
            go_back = true;
            break;

        case back:
            go_back = true;
            break;
        }
    }
}


void Menu::all_characters() {
    cout << endl;
    for (auto character : characters) {
        if (auto person = dynamic_cast<Role<Person>*>(character)) {
            person->print_stats();
        }
        else if (auto creature = dynamic_cast<Species<Creature>*>(character)) {
            creature->print_stats();
        }
        else if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            investigator->print_stats();
        }
        else if (auto eldritch = dynamic_cast<Species<EldritchHorror>*>(character)) {
            eldritch->print_stats();
        }
        cout << endl;
    }
}


void Menu::all_investigators() {
    cout << endl;
    for (auto character : characters) {
        if (auto person = dynamic_cast<Role<Investigator>*>(character)) {
            person->print_stats();
            cout << endl;
        }
    }
}


void Menu::chars_to_file(string filename) {
    string data;

    data = "----Here are all the characters----\n";

    for (auto character : characters) {
        string line;
        if (auto person = dynamic_cast<Role<Person>*>(character)) {
            line += "\n" + person->get_name() + "\n";
            line += " - " + person->get_role_name() + "\n";
            line += " - " + person->type.get_type() + "\n";
            line += " - Life: " + to_string(person->type.get_life_stat()) + "\n";
            line += " - Strength: " + to_string(person->type.get_strength_stat()) + "\n";
            line += " - Intelligence: " + to_string(person->type.get_intelligence_stat()) + "\n";
            line += " - Gender: " + person->type.get_gender() + "\n";
            line += " - Fear: " + to_string(person->type.get_fear_stat()) + "\n";
        }
        else if (auto creature = dynamic_cast<Species<Creature>*>(character)) {
            line += "\n" + creature->get_name() + "\n";
            line += " - " + creature->get_role_name() + "\n";
            line += " - " + creature->type.get_type() + "\n";
            line += " - Life: " + to_string(creature->type.get_life_stat()) + "\n";
            line += " - Strength: " + to_string(creature->type.get_strength_stat()) + "\n";
            line += " - Intelligence: " + to_string(creature->type.get_intelligence_stat()) + "\n";
            line += " - " + creature->type.get_natural() + "\n";
            line += " - Disquiet: " + to_string(creature->type.get_disquiet_stat()) + "\n";
        }
        else if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            line += "\n" + investigator->get_name() + "\n";
            line += " - " + investigator->get_role_name() + "\n";
            line += " - " + investigator->type.get_type() + "\n";
            line += " - Life: " + to_string(investigator->type.get_life_stat()) + "\n";
            line += " - Strength: " + to_string(investigator->type.get_strength_stat()) + "\n";
            line += " - Intelligence: " + to_string(investigator->type.get_intelligence_stat()) + "\n";
            line += " - Gender: " + investigator->type.get_gender() + "\n";
            line += " - Fear: " + to_string(investigator->type.get_fear_stat()) + "\n";
            line += " - Terror: " + to_string(investigator->type.get_terror_stat()) + "\n";
        }
        else if (auto eldritch = dynamic_cast<Species<EldritchHorror>*>(character)) {
            line += "\n" + eldritch->get_name() + "\n";
            line += " - " + eldritch->get_role_name() + "\n";
            line += " - " + eldritch->type.get_type() + "\n";
            line += " - Life: " + to_string(eldritch->type.get_life_stat()) + "\n";
            line += " - Strength: " + to_string(eldritch->type.get_strength_stat()) + "\n";
            line += " - Intelligence: " + to_string(eldritch->type.get_intelligence_stat()) + "\n";
            line += " - " + eldritch->type.get_natural() + "\n";
            line += " - Disquiet: " + to_string(eldritch->type.get_disquiet_stat()) + "\n";
            line += " - Traumatism: " + to_string(eldritch->type.get_traumatism_stat()) + "\n";

        }

        data += line;
    }

    fstream file;
    file.open(filename, ios::out | ios::trunc);
    file << data;
    file.close();
}


void Menu::invs_to_file(string filename) {
    string data;

    data = "----Here are all the investigators----\n";

    for (auto character : characters) {
        string line;
        if (auto investigator = dynamic_cast<Role<Investigator>*>(character)) {
            line += "\n" + investigator->get_name() + "\n";
            line += " - " + investigator->get_role_name() + "\n";
            line += " - " + investigator->type.get_type() + "\n";
            line += " - Life: " + to_string(investigator->type.get_life_stat()) + "\n";
            line += " - Strength: " + to_string(investigator->type.get_strength_stat()) + "\n";
            line += " - Intelligence: " + to_string(investigator->type.get_intelligence_stat()) + "\n";
            line += " - Gender: " + investigator->type.get_gender() + "\n";
            line += " - Fear: " + to_string(investigator->type.get_fear_stat()) + "\n";
            line += " - Terror: " + to_string(investigator->type.get_terror_stat());
            data += line + "\n";
        }
    }

    fstream file;
    file.open(filename, ios::out | ios::trunc);
    file << data;
    file.close();
}


void Menu::view_characters(){
    int option_len = 3;
    enum Choice {console = 1, file, back};
    enum InvChoice {all = 1, inv};

    cout << "\n1) View all characters\n2) View only Investigators\n" << endl;
    bool asking = true;
    string inv_option;
    while (asking) {
        cout << "Enter option: ";
        cin >> inv_option;
        if (valid_option(inv_option, 2) != true) {
            cout << "Invalid option!\n" << endl;
            continue;
        }
        asking = false;
        break;
    }
    InvChoice inv_c = InvChoice(stoi(inv_option));

    
    bool go_back = false;
    while(go_back == false) {
        cout << "\n1) Print to console\n2) Print to file\n3) Go Back\n" << endl;
        string option;
        cout << "Enter option: ";
        cin >> option;

        if (valid_option(option, option_len) != true){
            cout << "Invalid option!\n" << endl;
            continue;
        }

        Choice my_choice = Choice(stoi(option));
        string filename;
        
        switch(my_choice){
        case console:
            if (inv_option == "1")
                all_characters();
            else if (inv_option == "2")
                all_investigators();
            go_back = true;
            break;
        
        case file:
            cout << "\nWhat should be the name of the file? ";
            cin >> filename;
            if (inv_option == "1")
                chars_to_file(filename);
            else if (inv_option == "2")
                invs_to_file(filename);
            go_back = true;
            break;

        case back:
            go_back = true;
            break;
        }
    }
}


void Menu::view_single(){
    cout << "\n\n----Here are the roles available----" << endl;

    for (int i = 0; i < roles.size(); i++){
        cout << "\n" << i + 1 << ") " << roles[i][1] << endl;
        cout << " - " << roles[i][0] << endl;
    }

    cout << "\n" << roles.size() + 1 << ") Go back\n " << endl;


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

        break;
    }


    cout << "\n" << roles[stoi(option)-1][1] << endl;
    cout << " - " << roles[stoi(option)-1][0] << endl;
    cout << " - Life: " << roles[stoi(option)-1][2] << endl;
    cout << " - Strength: " << roles[stoi(option)-1][3] << endl;
    cout << " - Intelligence: " << roles[stoi(option)-1][4] << endl;

    if (roles[stoi(option)-1][0] == "Person" || roles[stoi(option)-1][0] == "Investigator"){
        cout << " - " << roles[stoi(option)-1][5] << endl;
        cout << " - Fear: " << roles[stoi(option)-1][6] << endl;
    }
    else if (roles[stoi(option)-1][0] == "Creature" || roles[stoi(option)-1][0] == "EldritchHorror"){
        if (roles[stoi(option)-1][5] == "true"){
            cout << " - Natural " << endl;
        }
        else {
            cout << " - Unnatural " << endl;
        }
        cout << " - Disquiet: " << roles[stoi(option)-1][6] << endl;
    }

    if (roles[stoi(option)-1][0] == "Investigator"){
        cout << " - Terror: " << roles[stoi(option)-1][7] << endl;
    }
    else if (roles[stoi(option)-1][0] == "EldritchHorror"){
        cout << " - Traumatism: " << roles[stoi(option)-1][7] << endl;
    }
}


void Menu::view_menu(){
    int option_len = 4;
    enum Choice {role = 1, character, single, back};
    
    bool go_back = false;
    while(go_back == false) {
        cout << view_options << endl;
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
            view_roles();
            go_back = true;
            break;
        
        case character:
            view_characters();
            go_back = true;
            break;

        case single:
            view_single();
            go_back = true;
            break;

        case back:
            go_back = true;
            break;
        }
    }
}



//------------------------------ Switch roster ----------------------------------

void Menu::switch_roster(){
    string filename;

    cout << "What's the name of the roster file? ";
    cin >> filename;
    
    rosterFileName = filename;
    get_characters();

    all_characters();
}