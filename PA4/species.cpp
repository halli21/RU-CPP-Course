#include <iostream>

using namespace std;



template <class T>
class Species{
public:
    Species(){this->name = "unknown";};
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

    T type;
    

protected:
    string name;
};