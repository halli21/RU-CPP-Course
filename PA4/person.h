
using namespace std;


#include "being.h"


class Person : public Being{
public:
    Person();
    Person(int life, int strength, int intel, string gender, int fear);
    void print_data();

    string get_gender();
    int get_fear_stat();
    
    void edit_gender(string gender);
    void edit_fear(int value);

    int get_life_stat(){return Being::get_life_stat();};
    int get_strength_stat(){return Being::get_strength_stat();};
    int get_intelligence_stat(){return Being::get_intelligence_stat();};
   
    void edit_life(int value){Being::edit_life(value);};
    void edit_strength(int value){Being::edit_strength(value);};
    void edit_intelligence(int value){Being::edit_intelligence(value);};

    void print_stats();



protected:
    string gender;
    int fear;

    int min_fear_stat;
    int max_fear_stat;
    
    int valid_value(int value, int min, int max);

    
};