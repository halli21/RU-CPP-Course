
using namespace std;

#define MAX_STAT 3
#define MIN_STAT 0

#include "creature.h"



class EldritchHorror : public Creature{
public:
    EldritchHorror();
    EldritchHorror(int traumatism);
    void print_data();

protected:
    int traumatism;

private:
    int valid_value(int value);
};