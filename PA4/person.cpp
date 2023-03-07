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

void Person::edit_gender(string gender) {
    this->gender = gender;

}
void Person::edit_fear(int value) {
    this->gender = valid_value(value, min_fear_stat, max_fear_stat);
}
