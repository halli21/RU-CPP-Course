
using namespace std;



#include "creature.h"



class EldritchHorror : public Creature{
public:
    EldritchHorror();
    EldritchHorror(int traumatism);
    void print_data();

    int get_traumatism_stat();
    void edit_traumatism(int value);

    
    void edit_natural(bool natural){return Creature::edit_natural(natural);};
    void edit_disquiet(int value){return Creature::edit_disquiet(value);};

    int get_life_stat(){return Creature::get_life_stat();};
    int get_strength_stat(){return Creature::get_strength_stat();};
    int get_intelligence_stat(){return Creature::get_intelligence_stat();};
   
    void edit_life(int value){Creature::edit_life(value);};
    void edit_strength(int value){Creature::edit_strength(value);};
    void edit_intelligence(int value){Creature::edit_intelligence(value);};

    void print_stats();

protected:
    int traumatism;

    int min_traumatism_stat;
    int max_traumatism_stat;

    int valid_value(int value, int min, int max);
};