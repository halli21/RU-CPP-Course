#include <map>

using namespace std;



class HuffmanNode {       
   public:
      string character;
      int frequency;

      HuffmanNode* left;   
      HuffmanNode* right;
 
      HuffmanNode(string data, int freq) {
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

      void encode(vector<char>& data, string output_filename);

      void decode(map<string, string> code_map, string code_string, string output_filename);

      virtual ~Huffman();

   private:
      HuffmanNode* build_tree_from_byte_map(map<string, int> byte_map);

      void get_codes(HuffmanNode* root, map<string, string> &code_map, string code);

      string huffman_encoding(map<string, string> code_map, vector<char>& data);

      HuffmanNode* build_tree_from_code_map(map<string, string> code_map);

    

};
