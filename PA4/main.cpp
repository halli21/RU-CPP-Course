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

    cout << thing->type.get_gender() << endl;

    thing->type.edit_gender("Yellow");

    cout << thing->type.Being.get_life() << endl;


    return 0;
}
