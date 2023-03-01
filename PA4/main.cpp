#include <iostream>

#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "being.h"

using namespace std;

// int argc, char* argv[]

int main() {

    Being halli;

    Being arnar(111, 4, -10);

    halli.print_being();

    arnar.print_being();

    return 0;
}
