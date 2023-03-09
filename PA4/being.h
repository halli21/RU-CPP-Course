



#ifndef MY_BEING_CLASS_su389ru4
#define MY_BEING_CLASS_su389ru4


using namespace std;


class Being{
public:
    Being();
    Being(int life, int strength, int intelligence);
    int get_life_stat();
    int get_strength_stat();
    int get_intelligence_stat();
   
    void edit_life(int value);
    void edit_strength(int value);
    void edit_intelligence(int value);

    void print_stats();



protected:
    int life;
    int strength;
    int intelligence;

    int min_stat;
    int max_stat;

    int valid_value(int value, int min, int max);

};

#endif
