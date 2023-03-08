#include <iostream>

#include "investigator.h"

using namespace std;


Investigator::Investigator() {
    this->terror = 2;

    this->min_terror_stat = 0;
    this->max_terror_stat = 3;
}

int Investigator::valid_value(int value, int min, int max) {
    return Person::valid_value(value, min_terror_stat, max_terror_stat);
}

Investigator::Investigator(int terror) {
    this->terror = valid_value(terror, min_terror_stat, max_terror_stat);
}

void Investigator::print_data() {
   
    cout << "my being stats: "<< life << " " << strength << " " << intelligence << endl;
    cout << "my person stats: "<< gender << " " << fear << endl;
    cout << "my investigator stats: "<< terror << endl;
}

int Investigator::get_terror_stat() {
    return this->terror;
}

void Investigator::edit_terror(int value) {
    this->terror = valid_value(value, min_terror_stat, max_terror_stat);
}

void Investigator::print_stats(){
    Person::print_stats();
    cout << " - Terror: " << this->terror << endl;
}