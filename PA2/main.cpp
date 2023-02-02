#include <iostream>
#include "game.h"

using namespace std;



int main() {
    Game test;


    std::cout << "Word before random call: " << test.word << std::endl;



    test.get_random_word();


    std::cout << "Word after random call: " << test.word << std::endl;



    return 0;

}