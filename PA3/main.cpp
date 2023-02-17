#include <iostream>
#include <fstream>
#include <string>
#include <map>

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

    //string input_filename = "original.txt";
    //string output_filename = "encoded_file.txt";

    string input_filename = "encoded_file.txt";
    string output_filename = "decoded.txt";

    string input_string;

    map<char, string> code_map;
    bool code = false;
    string code_string;

    string line;

    ifstream fin;
    fin.open(input_filename);

    while(fin) {
        fin >> line;

        if (line == "\\") {
            code = true;
            continue;
        }
        
        if (code) {
            code_string += line + '\n';
        }
        else {
            char character = line.at(0);   // trick til að converta i character, vildi ekki breyta code map
            fin >> line;
            code_map[character] += line;
        }

        if( fin.eof() ) break;
    }

    fin.close();

    /*
    if (mode == "-e") {

        while(fin) {
            fin >> line;

            input_string += line + "\n";
            
            if( fin.eof() ) break;
        }   

        fin.close();

        hman.encode(input_string, output_filename);
    } 
    else if (mode == "-d") {
        cout << "decode" << endl;
    }
    */

    //hman.encode(input_string, output_filename);

    hman.decode(code_map, code_string, output_filename);

    return 0;

}
