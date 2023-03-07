
using namespace std;

#define MAX_STAT 10
#define MIN_STAT 0

#include "being.h"


class Creature : public Being{
public:
    Creature();
    Creature(bool natural, int disquiet);
    void print_data();

protected:
    bool natural;
    int disquiet;

private:
    int valid_value(int value);
};