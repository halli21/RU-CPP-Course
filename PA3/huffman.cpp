#include <iostream>
#include <string.h>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

#include "huffman.h"

using namespace std;



Huffman::Huffman() {
   

}


HuffmanNode* Huffman::build_tree_from_char_map(map<char, int> char_map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>,Compare> pq;

    for (auto it = char_map.begin(); it != char_map.end(); it++) {
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


string Huffman::huffman_encoding(map<char, string> code_map, string input_string) {

    string encoded_text;

    for (int i = 0; i < input_string.length(); i++) {
        char current_char = input_string[i];

        if (current_char == '\n'){
            encoded_text += '\n';
        } 
        else if (current_char == ' '){
            encoded_text += ' ';
        } 
        else {
            encoded_text += code_map[current_char];
        }
    }

    return encoded_text;
}


void Huffman::encode(string input_string, string output_filename) {
    map<char, int> char_map;

    for (char c = 'A'; c <= 'Z'; c++) {
        char_map[c] = 0;
    }

    char_map['_'] = 0;

    for (char c = 'a'; c <= 'z'; c++) {
        char_map[c] = 0;
    }

    for (int i = 0; i < input_string.length(); i++) {
        char current_char = input_string[i];

        if (char_map.find(current_char) != char_map.end()) {
            char_map[current_char] += 1;
        } 
    }


    HuffmanNode* root = build_tree_from_char_map(char_map);

    map<char, string> code_map;
    get_codes(root, code_map, "");

    string encoded_text = huffman_encoding(code_map, input_string);


    ofstream fout;
    fout.open(output_filename);


    for (auto it = char_map.begin(); it != char_map.end(); it++) {
        if (it->second > 0) {
            fout << it->first << " " << code_map[it->first] << endl;
        }
    }
    fout << "\\" << "\n" << endl;

    fout << encoded_text;

    fout.close();
}




HuffmanNode* Huffman::build_tree_from_code_map(map<char, string> code_map) {

    HuffmanNode* root = new HuffmanNode('*', 0);

    for (auto it = code_map.begin(); it != code_map.end(); it++) {

        HuffmanNode* current_node = root;

        for (char code : it->second) {
            if (code == '1') {
                if (current_node->left == nullptr) {
                    current_node->left = new HuffmanNode('*', 0);
                }
                current_node = current_node->left;
            } 
            else if (code == '0') {
                if (current_node->right == nullptr) {
                    current_node->right = new HuffmanNode('*', 0);
                }
                current_node = current_node->right;
            }
        }

        current_node->character = it->first;
    }

    return root;
}


void Huffman::decode(map<char, string> code_map, string code_string, string output_filename) {

    HuffmanNode* root = build_tree_from_code_map(code_map);

    ofstream fout;
    fout.open(output_filename);

    HuffmanNode* current_node = root;


    for (int i = 0; i < code_string.length(); i++) {

        char character = code_string[i];

        if (character == '\n') {
            fout << '\n';
            continue;
        }
        else if (character == '1') {
            current_node = current_node->left;
        } 
        else if (character == '0') {
            current_node = current_node->right;
        }
        if (current_node->left == nullptr && current_node->right == nullptr) {
            fout << current_node->character;
            current_node = root;
        }
    
    }

    fout.close();
}


Huffman::~Huffman() {
     
        
}