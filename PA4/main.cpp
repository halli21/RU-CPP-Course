#include <iostream>


#include "investigator.h"


using namespace std;

// int argc, char* argv[]

int main() {

    Being halli;
    halli.print_data();

    Being arnar(111, 4, -10);
    arnar.print_data();

    Person frosti;
    frosti.print_data();

    Investigator logi;
    logi.print_data();

    return 0;
}
