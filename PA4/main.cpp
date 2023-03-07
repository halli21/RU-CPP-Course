#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


#include "investigator.h"


using namespace std;


#include "role.cpp"




// int argc, char* argv[]

int main() {

    vector<vector<string>> roles;
    vector<vector<string>> characters;

    fstream rolesFile;
    rolesFile.open("roles.txt",ios::in);
    string tp;
    while(getline(rolesFile, tp)){ 
        vector<string> temp;
        stringstream ss(tp);
        while ( ss.good() ) {
            string substr;
            getline( ss, substr, ';' );
            temp.push_back( substr );
        }

        roles.push_back(temp);
    }
    rolesFile.close();


    fstream charsFile;
    charsFile.open("characters.txt",ios::in);
    string tp2;
    while(getline(charsFile, tp2)){ 
        vector<string> temp;
        cout << "tp2 " << tp2 << endl;
        stringstream ss(tp2);
        while ( ss.good() ) {
            string substr;
            getline( ss, substr, ';' );
            temp.push_back( substr );
        }

        characters.push_back(temp);
    }
    charsFile.close();

    //printing roles vector
    /*cout << "Roles: " << endl;
    for (int i = 0; i < roles.size(); i++) {
        for (int x = 0; x < roles[i].size(); x++) {
            cout << roles[i][x] << " - ";
        }
        cout << endl;
    }*/

    //printing characters vector
    /*for (int i = 0; i < characters.size(); i++) {
        for (int x = 0; x < characters[i].size(); x++) {
            cout << characters[i][x] << " - ";
        }
        cout << endl;
    }*/


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
