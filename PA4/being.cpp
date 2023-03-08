#include <iostream>

#include "being.h"

using namespace std;


Being::Being() {
    this->life = 5;
    this->strength = 5;
    this->intelligence = 5;
    
    this->min_stat = 0;
    this->max_stat = 10;
}

int Being::valid_value(int value, int min, int max) {
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

Being::Being(int life, int strength, int intelligence) {
    this->life = valid_value(life, min_stat, max_stat);
    this->strength = valid_value(strength, min_stat, max_stat);
    this->intelligence = valid_value(intelligence, min_stat, max_stat);
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
    this->life = valid_value(value, min_stat, max_stat);
}
void Being::edit_strength(int value) {
    this->strength = valid_value(value, min_stat, max_stat);
}
void Being::edit_intelligence(int value) {
    this->intelligence = valid_value(value, min_stat, max_stat);
}


void Being::print_stats(){
    cout << " - Life: " << this->life << endl;
    cout << " - Strength: " << this->strength << endl;
    cout << " - Intelligence: " << this->intelligence << endl;
}