using namespace std;

#define MAX_STAT 10
#define MIN_STAT 0


class Being{
public:
    Being();
    Being(int life, int strength, int intelligence);
    void print_data();
    int get_life_stat();
    int get_strength_stat();
    int get_intelligence_stat();
   
    void edit_life(int value);
    void edit_strength(int value);
    void edit_intelligence(int value);

protected:
    int life;
    int strength;
    int intelligence;

private:
    int valid_value(int value);
};
