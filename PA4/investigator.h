
using namespace std;


#include "person.h"



class Investigator : public Person{
public:
    Investigator();
    Investigator(int terror);
    void print_data();

    int get_terror_stat();
    void edit_terror(int value);

    string get_gender(){return Person::get_gender();};
    int get_fear_stat(){return Person::get_fear_stat();};
    
    void edit_gender(string gender){return Person::edit_gender(gender);};
    void edit_fear(int value){return Person::edit_fear(value);};

    int get_life_stat(){return Person::get_life_stat();};
    int get_strength_stat(){return Person::get_strength_stat();};
    int get_intelligence_stat(){return Person::get_intelligence_stat();};
   
    void edit_life(int value){Person::edit_life(value);};
    void edit_strength(int value){Person::edit_strength(value);};
    void edit_intelligence(int value){Person::edit_intelligence(value);};

    void print_stats();

    string get_type(){return "Investigator";};

    void edit_investigator();

protected:
    int terror;

    int min_terror_stat;
    int max_terror_stat;

private:
    int valid_value(int value, int min, int max);

    bool valid_option(string option, int option_len);
};