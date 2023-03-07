
using namespace std;

#define MAX_STAT 3
#define MIN_STAT 0

#include "person.h"



class Investigator : public Person{
public:
    Investigator();
    Investigator(int terror);
    void print_data();

protected:
    int terror;

private:
    int valid_value(int value);
};