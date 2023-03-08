#include <iostream>

#include "creature.h"

using namespace std;


Creature::Creature() {
    this->natural = true;
    this->disquiet = 5;

    this->min_disquiet_stat = 0;
    this->max_disquiet_stat = 10;
}

int Creature::valid_value(int value, int min, int max) {
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

Creature::Creature(bool natural, int disquiet) {
    this->natural = natural;
    this->disquiet = valid_value(disquiet, min_disquiet_stat, max_disquiet_stat);
}

void Creature::print_data() {
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my creature stats: "<< natural << " " << disquiet << endl;
}


bool Creature::get_natural() {
    return this->natural;

}
int Creature::get_disquiet_stat() {
    return this->disquiet;
}

void Creature::edit_natural(bool natural) {
    this->natural = natural;

}
void Creature::edit_disquiet(int value) {
    this->disquiet = valid_value(value, min_disquiet_stat, max_disquiet_stat);
}



void Creature::print_stats(){
    Being::print_stats();
    if (this->natural == true){
        cout << " - Natural " << endl;
    }
    else {
        cout << " - Unnatural " << endl;
    }
    cout << " - Disquiet: " << this->disquiet << endl;
}
