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

    cout << "Roles: " << endl;
    for (int i = 0; i < roles.size(); i++) {

        cout << roles[i] << endl;
    }



    Being halli;
    halli.print_data();

    Role<Person> *thing = new Role<Person>("Reporter");
    

    cout << thing << endl;

    thing->change_name("halli");

    cout << thing << endl;

    cout << thing->type.get_gender() << endl;

    thing->type.edit_gender("Yellow");

    cout << thing->type.Being.get_life() << endl;


    Person Siggi(10,10,10,"male",2);
    Siggi.print_data();

    return 0;
}
