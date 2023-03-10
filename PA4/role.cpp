#include <iostream>

#include "character.cpp"


using namespace std;




template <class T>
class Role : public Character{
public:
    Role(){this->name = "unknown";};
    Role(string name){this->name = name;};
    void print_data() {
        std::cout << "I am a role" << std::endl;
    }

    friend ostream &operator<<(ostream &out, const Role<T>* character) {
        out << character->name;
        return out;
    }

    void change_name(string name) {
        this->name = name;
    }

    void edit_name(){
        string value;
        cout << "Enter value change: ";
        cin >> value;
        this->name = value;
    }

    void print_stats() {
        cout << this->name << endl;
        type.print_stats();
    }

    T type;
    
protected:
    string name;

};