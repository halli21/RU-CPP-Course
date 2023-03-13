#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;



class Being{
public:
    string name;
    Being(){this->name = "Halli";};
    virtual void print_character(){cout << name << endl;};
    
};


class Person : public Being{
public:
    string life;
    Person(){this->life = "5";};
    void print_character(){
        Being::print_character();
        cout << life << endl;
        };
    
};


class Poop : public Person{
public:
    string poopy_level;
    Poop(){this->poopy_level = "10";};
    void print_character(){
        Person::print_character();
        cout << poopy_level << endl;
        };
    
};


int main() {

    Being *yes = new Person;

    Being *no = new Poop;

    list<Being*> list;

    list.push_back(yes);
    list.push_back(no);

    for (Being *character : list) {
        cout << "\n" << endl;
        character->print_character();
    }

    return 0;
}
