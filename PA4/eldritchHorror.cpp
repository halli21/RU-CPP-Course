#include <iostream>

#include "eldritchHorror.h"

using namespace std;


EldritchHorror::EldritchHorror() {
    this->traumatism = 2;
    this->disquiet = 10;
}

int EldritchHorror::valid_value(int value) {
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

EldritchHorror::EldritchHorror(int traumatism) {
    this->traumatism = valid_value(traumatism);
}

void EldritchHorror::print_data() {
   
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< natural << " " << disquiet << endl;
    cout << "my eldritchHorror stats: "<< traumatism << endl;
}