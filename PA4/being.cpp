#include <iostream>

#include "being.h"

using namespace std;


Being::Being() {
    this->life = 5;
    this->strength = 5;
    this->intelligence = 5;
}

int Being::valid_value(int value) {
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

Being::Being(int life, int strength, int intelligence) {
    this->life = valid_value(life);
    this->strength = valid_value(strength);
    this->intelligence = valid_value(intelligence);
}


void Being::print_being() {
    cout << "my stats: "<< life << " " << strength << " " << intelligence << endl;
}