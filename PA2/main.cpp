#include <iostream>
#include "game.h"

using namespace std;



int main() {
    Game test;


    std::cout << "Word before random call: " << test.get_original_word() << std::endl;


    test.get_random_word();


    std::cout << "Word after random call: " << test.get_original_word() << std::endl;


    test.scramble_word();


    std::cout << "Word after scramble call: " << test.get_scrambled_word() << std::endl;



    return 0;

}