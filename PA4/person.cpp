#include <iostream>

#include "person.h"

using namespace std;


Person::Person() {
    this->gender = "undefined";
    this->fear = 5;
}

int Person::valid_value(int value) {
    if (value < MIN_STAT) {
        return MIN_STAT;
    }
    else if (value > MAX_STAT) {
        return MAX_STAT;
    }
    else {
        return value;
    }
}

Person::Person(string gender, int fear) {
    this->gender = gender;
    this->fear = valid_value(fear);
}

void Person::print_data() {
    cout << "my person stats: "<< gender << " " << fear << endl;
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
}