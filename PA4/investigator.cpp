#include <iostream>

#include "investigator.h"

using namespace std;


Investigator::Investigator() {
    this->terror = 2;

    this->min_terror_stat = 0;
    this->max_terror_stat = 3;
}

int Investigator::valid_value(int value, int min, int max) {
    return Person::valid_value(value, min, max);
}

Investigator::Investigator(int terror) {
    this->terror = valid_value(terror, min_terror_stat, max_terror_stat);
}

void Investigator::print_data() {
   
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< gender << " " << fear << endl;
    cout << "my investigator stats: "<< terror << endl;
}

int Investigator::get_terror_stat() {
    return this->terror;
}

void Investigator::edit_terror(int value) {
    this->terror = valid_value(value, min_terror_stat, max_terror_stat);
}

void Investigator::print_stats(){
    Person::print_stats();
    cout << " - Terror: " << this->terror << endl;
}

bool Investigator::valid_option(string option, int option_len){
    char max = option_len + '0';
    if (1 == option.length() && (option[0] >= '1' && option[0] <= max)) {
        return true;
    }
    return false;
}

void Investigator::edit_investigator(){

    int option_len = 7;
    enum Choice {life = 1, strength, intelligence, gender, fear, terror, quit};

    string choices = "\n1) Life\n2) Strength\n3) Intelligence\n4) Gender\n5) Fear\n6) Terror\n7) Go Back\n";


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

        case gender:
            cout << "Enter value change: ";
            cin >> value;
            this->edit_gender(value);
            return;
        
        case fear:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_fear_stat, max_fear_stat);
            this->edit_fear(value_checked);
            return;

        case terror:
            cout << "Enter value change: ";
            cin >> value;
            try {
                num = stoi(value);
            } catch (...) {
                cout << "\nNeeds to be number!" << endl;
                break;
            }
            value_checked = this->valid_value(num, min_terror_stat, max_terror_stat);
            this->edit_terror(value_checked);
            return;

        case quit:
            return;
        }
    }
}