using namespace std;

#define MAX_STAT 10
#define MIN_STAT 0


class Being{
public:
    Being();
    Being(int life, int strength, int intelligence);
    void print_being();

protected:
    int life;
    int strength;
    int intelligence;

private:
    int valid_value(int value);
};
