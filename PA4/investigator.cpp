#include <iostream>

#include "investigator.h"

using namespace std;


Investigator::Investigator() {
    this->terror = 2;
}

int Investigator::valid_value(int value) {
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

Investigator::Investigator(int terror) {
    this->fear = valid_value(terror);
}

void Investigator::print_data() {
   
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< gender << " " << fear << endl;
    cout << "my investigator stats: "<< terror << endl;
}