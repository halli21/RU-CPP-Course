

class DynamicArray {       
 public:
    DynamicArray();

    void push_back(const char*);

    int get_size();

    char* operator[](int index) const;

    void remove(int index);

    DynamicArray(const DynamicArray& other);

    virtual ~DynamicArray();


 private:
    char** arr;
    int size;
    int capacity;

};
