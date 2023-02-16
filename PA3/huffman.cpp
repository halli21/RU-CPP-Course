#include <iostream>
#include <string.h>
#include <map>
#include <queue>
#include <vector>

#include "huffman.h"

using namespace std;



Huffman::Huffman() {
   

}

HuffmanNode* Huffman::build_tree(map<char, int> char_map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>,Compare> pq;
    std::map<char, int>::iterator it;

    for (it = char_map.begin(); it != char_map.end(); it++) {
        if (it->second > 0) {
            HuffmanNode *node = NULL; 
            node = new HuffmanNode(it->first, it->second);
            pq.push(node); 
        }
    }

    while(pq.size() != 1) {

        HuffmanNode* left = pq.top();
        pq.pop();

        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* node = new HuffmanNode('*', left->frequency + right->frequency);
        node->left = left;
        node->right = right;
 
        pq.push(node);
    }

    return pq.top();
}


void Huffman::get_codes(HuffmanNode* root, map<char, string> &code_map, string code) {

    if (root->left == nullptr && root->right == nullptr) {
        code_map[root->character] = code;
        return;
    }

    get_codes(root->left, code_map, code + "1");
    get_codes(root->right, code_map, code + "0");
}



void Huffman::encode(string input, string output_filename) {
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

    HuffmanNode* root = build_tree(char_map);

    map<char, string> code_map;
    get_codes(root, code_map, "");


    std::map<char, int>::iterator it;

    for (it = char_map.begin(); it != char_map.end(); it++) {
        if (it->second > 0) {
            cout << it->first << " : " <<code_map[it->first] << endl;
        }
    }

}





Huffman::~Huffman() {
     
        
}