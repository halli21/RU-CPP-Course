#include <iostream>
#include <fstream>
#include <string>

#include "huffman.h"



using namespace std;

// int argc, char* argv[]

int main() {

    /*

    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " [-e|-d] input.txt output.txt" << std::endl;
        return 1;
    }

    string mode = argv[1];
    string input_filename = argv[2];
    string output_filename = argv[3];

    */

    Huffman hman;

    string input_filename = "text_file_01_org.txt";

    string input_string;
    string line;



    ifstream fin;
    fin.open(input_filename);

    while(fin) {
        fin >> line;
        input_string += line;
        if( fin.eof() ) break;
    }

    fin.close();

    hman.encode(input_string);

    return 0;

}
