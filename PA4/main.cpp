#include <iostream>
#include <vector>
#include <string>
#include <fstream>


#include "investigator.h"


using namespace std;


#include "role.cpp"




// int argc, char* argv[]

int main() {

    vector<string> roles;

    fstream rolesFile;
    rolesFile.open("roles.txt",ios::in);
    string tp;
    while(getline(rolesFile, tp)){ //read data from file object and put it into string.
        //cout << tp << "\n"; //print the data of the string
        roles.push_back(tp);
    }
    rolesFile.close();

    //cout << "Roles: " << endl;
    for (int i = 0; i < roles.size(); i++) {

        //cout << roles[i] << endl;
    }


    /*
    Role<Person> *thing = new Role<Person>("Reporter");
    

    cout << thing << endl;

    thing->change_name("halli");

    cout << thing << endl;

    cout << thing->type.get_gender() << endl;

    thing->type.edit_gender("Yellow");

    cout << thing->type.get_gender() << endl;

    cout << thing->type.get_life_stat() << endl;

    thing->type.edit_life(8);

    cout << thing->type.get_life_stat() << endl;

    */


    Role<Investigator> *thing = new Role<Investigator>("Lice Spice");

    cout << thing << endl;

    thing->change_name("Ice Spice");

    cout << thing << endl;

    cout << thing->type.get_terror_stat() << endl;

    thing->type.edit_terror(10);

    cout << thing->type.get_terror_stat() << endl;

    thing->type.edit_terror(1);

    cout << thing->type.get_terror_stat() << endl;

    cout << thing->type.get_gender() << endl;

    thing->type.edit_gender("Yellow");

    cout << thing->type.get_gender() << endl;

    cout << thing->type.get_life_stat() << endl;

    thing->type.edit_life(-10);

    cout << thing->type.get_life_stat() << endl;

    return 0;
}
