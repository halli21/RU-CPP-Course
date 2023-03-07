#include <iostream>

#include "creature.h"

using namespace std;


Creature::Creature() {
    this->natural = true;
    this->disquiet = 5;
}

int Creature::valid_value(int value) {
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

Creature::Creature(bool natural, int disquiet) {
    this->natural = natural;
    this->disquiet = valid_value(disquiet);
}

void Creature::print_data() {
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my creature stats: "<< natural << " " << disquiet << endl;
}