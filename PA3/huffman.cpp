#include <iostream>
#include <string.h>
#include <map>
#include <queue>

#include "huffman.h"

using namespace std;



Huffman::Huffman() {
   

}

void Huffman::build_tree(string input, map<char, int> char_map) {
    priority_queue<HuffmanNode> pq;
    std::map<char, int>::iterator it;

    for (it = char_map.begin(); it != char_map.end(); it++) {
        if (it->second > 0) { 
            HuffmanNode node;
            node.character = it->first;
            node.count = it->second;

            pq.push(node);
        }
    }

    while(!pq.empty()) {
        cout << pq.top().character << " : " << pq.top().count << endl;
        pq.pop();
    }


}


void Huffman::encode(string input) {
    map<char, int> char_map;

    for (char c = 'A'; c <= 'Z'; c++) {
        char_map[c] = 0;
    }

    char_map['_'] = 0;

    for (char c = 'a'; c <= 'z'; c++) {
        char_map[c] = 0;
    }


    for (int i = 0; i < input.length(); i++) {
        char current_char = input[i];

        if (char_map.find(current_char) != char_map.end()) {
            char_map[current_char] += 1;
        } 
    }


    build_tree(input, char_map);

}



Huffman::~Huffman() {
     
        
}