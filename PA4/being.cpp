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

void Being::print_data() {
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
}


int Being::get_life_stat() {
    return this->life;
}
int Being::get_strength_stat() {
    return this->strength;
}
int Being::get_intelligence_stat() {
    return this->intelligence;
}


void Being::edit_life(int value) {
    this->life = valid_value(value);
}
void Being::edit_strength(int value) {
    this->strength = valid_value(value);
}
void Being::edit_intelligence(int value) {
    this->intelligence = valid_value(value);
}