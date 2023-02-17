#include <map>

using namespace std;



class HuffmanNode {       
   public:
      char character;
      int frequency;

      HuffmanNode* left;   
      HuffmanNode* right;
 
      HuffmanNode(char data, int freq) {
        character = data;
        frequency = freq;
        left = right = NULL;
      }
};


class Compare {
   public:
      bool operator()(HuffmanNode* a, HuffmanNode* b) {
         return a->frequency > b->frequency;
      }
};
 


class Huffman {       
   public:
      Huffman();

      void encode(string input, string output_filename);
    
      virtual ~Huffman();

   private:
      
      HuffmanNode* build_tree(map<char, int> char_map);

      void get_codes(HuffmanNode* root, map<char, string> &code_map, string code);

      string huffman_encoding(map<char, string> code_map, string input_string);

};
