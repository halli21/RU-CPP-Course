#include <iostream>
#include <string>

#include "creature.h"

using namespace std;


Creature::Creature() {
    this->natural = true;
    this->disquiet = 5;

    this->min_disquiet_stat = 0;
    this->max_disquiet_stat = 10;
}

int Creature::valid_value(int value, int min, int max) {
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

Creature::Creature(bool natural, int disquiet) {
    this->natural = natural;
    this->disquiet = valid_value(disquiet, min_disquiet_stat, max_disquiet_stat);
}

void Creature::print_data() {
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my creature stats: "<< natural << " " << disquiet << endl;
}


bool Creature::get_natural() {
    return this->natural;

}
int Creature::get_disquiet_stat() {
    return this->disquiet;
}

void Creature::edit_natural(bool natural) {
    this->natural = natural;

}
void Creature::edit_disquiet(int value) {
    this->disquiet = valid_value(value, min_disquiet_stat, max_disquiet_stat);
}



void Creature::print_stats(){
    Being::print_stats();
    if (this->natural == true){
        cout << " - Natural " << endl;
    }
    else {
        cout << " - Unnatural " << endl;
    }
    cout << " - Disquiet: " << this->disquiet << endl;
}

bool Creature::valid_option(string option, int option_len){
    char max = option_len + '0';
    if (1 == option.length() && (option[0] >= '1' && option[0] <= max)) {
        return true;
    }
    return false;
}



void Creature::edit_creature(){

    int option_len = 6;
    enum Choice {life = 1, strength, intelligence, natural, disquiet, quit};

    string choices = "\n1) Life\n2) Strength\n3) Intelligence\n4) Natural/Unnatural\n5) Disquiet\n6) Go Back\n";

    

    while (true){
        cout << "\n\n----Stats----" << endl;
        this->print_stats();
        cout << choices << endl;

        int num;
        string option;
        cout << "Enter option: ";
        cin >> option;
    
        if (valid_option(option, option_len) != true){
            cout << "\nInvalid option!\n" << endl;
            continue;
        }

        Choice my_choice = Choice(stoi(option));
        string value;
        int value_checked;

        switch(my_choice){
        case life:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!\n" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_stat, max_stat);
            this->edit_life(value_checked);
            break;

        case strength:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!\n" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_stat, max_stat);
            this->edit_strength(value_checked);
            break;

        case intelligence:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!\n" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_stat, max_stat);
            this->edit_intelligence(value_checked);
            break;

        case natural:
            cout << "Only values 'Natural' or 'Unnatural'" << endl;
            cout << "Enter value change: ";
            cin >> value;
            if (value == "Natural"){
                this->edit_natural(true);
            }
            else if (value == "Unnatural"){
                this->edit_natural(false);
            }
            else {
                cout << "\nInvalid option!\n" << endl;
            }
            break;
            

        case disquiet:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_disquiet_stat, max_disquiet_stat);
            this->edit_disquiet(value_checked);
            break;

        case quit:
            return;
        }
    }
}
