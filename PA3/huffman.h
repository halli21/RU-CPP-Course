#include <map>

using namespace std;



class HuffmanNode {       
   public:
      char character;
      int count;

      friend bool operator<(const HuffmanNode & one, const HuffmanNode &other) {
         return (one.count < other.count);
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
