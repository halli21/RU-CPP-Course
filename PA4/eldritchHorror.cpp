#include <iostream>

#include "eldritchHorror.h"

using namespace std;


EldritchHorror::EldritchHorror() {
    this->traumatism = 2;
    this->disquiet = 10;

    this->min_traumatism_stat = 0;
    this->max_traumatism_stat = 3;
}

int EldritchHorror::valid_value(int value, int min, int max) {
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

EldritchHorror::EldritchHorror(int traumatism) {
    this->traumatism = valid_value(traumatism, min_traumatism_stat, max_traumatism_stat);
}

void EldritchHorror::print_data() {
   
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< natural << " " << disquiet << endl;
    cout << "my eldritchHorror stats: "<< traumatism << endl;
}


int EldritchHorror::get_traumatism_stat() {
    return this->traumatism;
}

void EldritchHorror::edit_traumatism(int value) {
    this->traumatism = valid_value(value, min_traumatism_stat, max_traumatism_stat);

}