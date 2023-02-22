#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "huffman.h"



using namespace std;

// int argc, char* argv[]

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cout << "Usage: " << argv[0] << " [-c|-u] input.txt output.txt" << endl;
        return 1;
    }

    string mode = argv[1];
    string input_filename = argv[2];
    string output_filename = argv[3];
    

    Huffman hman;
  
    map<string, string> code_map;
    string code_string;
        
    string line;

    
    if (mode == "-c") {
        ifstream fin;
        fin.open(input_filename, ios::binary);

        fin.seekg (0, ios::end);
        int size = fin.tellg();
        fin.seekg (0, ios::beg);

        vector<char> data(size);

        fin.read(data.data(), size);
        fin.close();
        
        hman.encode(data, output_filename);

    } 
    else if (mode == "-u") {
        ifstream fin;
        fin.open(input_filename);

        for (int i = 0; i <= 255; i++) {
        getline(fin, line);
        if (not line.empty()) {
            string byte = "";
            byte += ((char)i);
            code_map[byte] = line;
            }
        }

        fin >> line;  // :(
        fin >> line;
        fin >> line;
        code_string += line;

        fin.close();

        hman.decode(code_map, code_string, output_filename);
    }
    
    
    return 0;
}
