
using namespace std;

#define MAX_STAT 10
#define MIN_STAT 0

#include "being.h"


class Person : public Being{
public:
    Person();
    Person(int life, int strength, int intel, string gender, int fear);
    void print_data();

protected:
    string gender;
    int fear;

private:
    int valid_value(int value);
};