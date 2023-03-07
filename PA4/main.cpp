#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


#include "menu.h"

enum Choice {create = 1, edit, view, quit};


// int argc, char* argv[]

int main() {

    Choice my_choice;
    Menu my_menu;

    while (true) {
        /* code */
    }
    


    /*
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
    */


    return 0;
}
