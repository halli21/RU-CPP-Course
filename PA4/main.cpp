#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>



#include "menu.h"

enum Choice {invalid, create, edit, view, quit};


int main() {

    Menu my_menu;
    Choice my_choice;
    
    while (true) {
        int int_choice = my_menu.get_action();
        Choice my_choice = Choice(int_choice);

        switch(my_choice){
        case create:
            my_menu.create_character_menu();
            break;

        case edit:
            my_menu.edit_menu();
            break;

        case view:
            cout << "view" << endl;
            break;

        case quit:
            return 0;
        
        default:
            cout << "Invalid option!\n" << endl;
            break;
        }
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
