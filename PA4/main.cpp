#include <iostream>


#include "investigator.h"


using namespace std;


#include "role.cpp"




// int argc, char* argv[]

int main() {


    Role<Person> *thing = new Role<Person>("Reporter");
    

    cout << thing << endl;

    thing->change_name("halli");

    cout << thing << endl;

    thing->type.print_data();

    return 0;
}
