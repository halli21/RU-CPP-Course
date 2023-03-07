#include <iostream>
#include <vector>
#include <string>
#include <fstream>


#include "investigator.h"


using namespace std;

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

    Being arnar(111, 4, -10);
    arnar.print_data();

    Person frosti;
    frosti.print_data();

    Investigator logi;
    logi.print_data();

    Person Siggi(10,10,10,"male",2);
    Siggi.print_data();
    
    return 0;
}
