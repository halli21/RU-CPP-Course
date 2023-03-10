#include <iostream>

#include "eldritchHorror.h"

using namespace std;


EldritchHorror::EldritchHorror() {
    this->traumatism = 2;
    Creature::edit_natural(false);
    Creature::edit_disquiet(10);
    

    this->min_traumatism_stat = 0;
    this->max_traumatism_stat = 3;
}

int EldritchHorror::valid_value(int value, int min, int max) {
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

EldritchHorror::EldritchHorror(int traumatism) {
    this->traumatism = valid_value(traumatism, min_traumatism_stat, max_traumatism_stat);
}

void EldritchHorror::print_data() {
   
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< natural << " " << disquiet << endl;
    cout << "my eldritchHorror stats: "<< traumatism << endl;
}


int EldritchHorror::get_traumatism_stat() {
    return this->traumatism;
}

void EldritchHorror::edit_traumatism(int value) {
    this->traumatism = valid_value(value, min_traumatism_stat, max_traumatism_stat);

}


void EldritchHorror::print_stats(){
    Creature::print_stats();
    cout << " - Traumatism: " << this->traumatism << endl;
}

bool EldritchHorror::valid_option(string option, int option_len){
    char max = option_len + '0';
    if (1 == option.length() && (option[0] >= '1' && option[0] <= max)) {
        return true;
    }
    return false;
}



void EldritchHorror::edit_eldritch(){

    int option_len = 7;
    enum Choice {life = 1, strength, intelligence, natural, disquiet, traumatism, quit};

    string choices = "\n1) Life\n2) Strength\n3) Intelligence\n4) Natural/Unnatural\n5) Disquiet\n6) Traumatism\n7) Go Back\n";


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
            return;

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
            return;

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
            return;

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
            return;
            

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
            return;

        case traumatism:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_traumatism_stat, max_traumatism_stat);
            this->edit_traumatism(value_checked);
            return;

        case quit:
            return;
        }
    }
}
