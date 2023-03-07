#include <iostream>

using namespace std;




template <class T>
class Role{
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
    T type;
    

protected:
    string name;

    
};