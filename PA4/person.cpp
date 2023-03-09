#include <iostream>

#include "person.h"

using namespace std;


Person::Person() {
    this->gender = "undefined";
    this->fear = 5;

    min_fear_stat = 0;
    max_fear_stat = 10;
}

int Person::valid_value(int value, int min, int max) {
    return Being::valid_value(value, min, max);
}

Person::Person(int life, int strength, int intel, string gender, int fear) 
: Being(life,strength,intel){
    this->gender = gender;
    this->fear = valid_value(fear, min_fear_stat, max_fear_stat);
}

void Person::print_data() {
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< gender << " " << fear << endl;
}

string Person::get_gender() {
    return this->gender;

}
int Person::get_fear_stat() {
    return this->fear;
}

void Person::edit_gender(string gender_change) {
    this->gender = gender_change;

}
void Person::edit_fear(int value) {
    this->fear = valid_value(value, min_fear_stat, max_fear_stat);
}


void Person::print_stats(){
    Being::print_stats();
    cout << " - Gender: " << this->gender << endl;
    cout << " - Fear: " << this->fear << endl;
}

bool Person::valid_option(string option, int option_len){
    char max = option_len + '0';
    if (1 == option.length() && (option[0] >= '1' && option[0] <= max)) {
        return true;
    }
    return false;
}

void Person::edit_person(){

    int option_len = 6;
    enum Choice {life = 1, strength, intelligence, gender, fear, quit};

    string choices = "\n1) Life\n2) Strength\n3) Intelligence\n4) Gender\n5) Fear\n6) Go Back\n";

    

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

        case gender:
            cout << "Enter value change: ";
            cin >> value;
            this->edit_gender(value);
            break;
        
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
            break;

        case quit:
            return;
        }
    }
}