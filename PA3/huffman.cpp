#include <iostream>
#include <string.h>
#include <map>
#include <queue>
#include <vector>

#include "huffman.h"

using namespace std;



Huffman::Huffman() {
   

}

void Huffman::build_tree(string input, map<char, int> char_map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>,Compare> pq;
    //priority_queue<HuffmanNode*> pq;
    std::map<char, int>::iterator it;

    for (it = char_map.begin(); it != char_map.end(); it++) {
        if (it->second > 0) {
            HuffmanNode *node = NULL; 
            node = new HuffmanNode(it->first, it->second);
            //node->character = it->first;
            //node->frequency = it->second;
            pq.push(node);
            cout << node->character << " : " << node->frequency  << endl;
        }
    }

    while(!pq.empty()) {

        HuffmanNode* left = pq.top();
        pq.pop();

        cout << left->character << " : " << left->frequency  << endl;

        HuffmanNode* right = pq.top();
        pq.pop();


        cout << right->character << " : " << right->frequency  << endl;

        HuffmanNode* node = new HuffmanNode('$', left->frequency + right->frequency);
        node->left = left;
        node->right = right;


        cout << node->character << " : " << node->frequency  << endl;
 
        pq.push(node);
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