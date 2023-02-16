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

      /*
      friend bool operator<(const HuffmanNode* one, const HuffmanNode* other) {
         return (one.frequency < other.frequency);
      }
      */
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
      

      void encode(string input);

    
      virtual ~Huffman();


   private:
      
      void build_tree(string input, map<char, int> char_map);

};
