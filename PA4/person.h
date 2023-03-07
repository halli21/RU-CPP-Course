
using namespace std;

#define MAX_STAT 10
#define MIN_STAT 0

#include "being.h"


class Person : public Being{
public:
    Person();
    Person(string gender, int fear);
    void print_data();
    string get_gender();
    int get_fear_stat();
    void edit_gender(string gender);
    void edit_fear(int value);

protected:
    string gender;
    int fear;

private:
    int valid_value(int value);
};