
using namespace std;


#include "being.h"


class Creature : public Being{
public:
    Creature();
    Creature(bool natural, int disquiet);
    void print_data();

    bool get_natural();
    int get_disquiet_stat();
    
    void edit_natural(bool natural);
    void edit_disquiet(int value);

    int get_life_stat(){return Being::get_life_stat();};
    int get_strength_stat(){return Being::get_strength_stat();};
    int get_intelligence_stat(){return Being::get_intelligence_stat();};
   
    void edit_life(int value){Being::edit_life(value);};
    void edit_strength(int value){Being::edit_strength(value);};
    void edit_intelligence(int value){Being::edit_intelligence(value);};

protected:
    bool natural;
    int disquiet;

    int min_disquiet_stat;
    int max_disquiet_stat;

    int valid_value(int value, int min, int max);
};