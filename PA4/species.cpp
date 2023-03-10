#include <iostream>

#include "character.cpp"

using namespace std;



template <class T>
class Species : public Character{
public:
    Species(){this->name = "unknown"; this->role_name = "unknown";};
    Species(string name){this->name = name;};
    void print_data() {
        std::cout << "I am a species" << std::endl;
    }

    friend ostream &operator<<(ostream &out, const Species<T>* character) {
        out << character->name;
        return out;
    }

    void change_name(string name) {
        this->name = name;
    }

    void change_role_name(string name) {
        this->role_name = name;
    }

    void edit_name() {
        string value;
        cout << "Enter value change: ";
        cin >> value;
        this->name = value;
    }

    void edit_role_name(){
        string value;
        cout << "Enter value change: ";
        cin >> value;
        this->role_name = value;
    }

    void print_stats() {
        cout << this->name << endl;
        cout << " - " << this->role_name << endl;
        type.print_stats();
    }

    string get_name() {
        return name;
    }

    string get_role_name() {
        return role_name;
    }

    T type;
    

protected:
    string name;
    string role_name;
};