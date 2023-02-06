#include <iostream>

#include "DynamicArray.h"


DynamicArray::DynamicArray() {
    size = 0;
    capacity = 1;
    arr = new char*[capacity];
}


void DynamicArray::push_back(const char* word) {
    if (size == capacity) {
        capacity *= 2;
        char** newArr = new char*[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[size] = new char[strlen(word) + 1];
    strcpy(arr[size], word);
    size++;
}


int DynamicArray::get_size() {
    return size;
}

char* DynamicArray::operator[](int index) const {
    if (index >= size) {
        std::cout << "Index out of range" << std::endl;
        return nullptr;
    }
    return arr[index];
}

DynamicArray::~DynamicArray() {
        for (int i = 0; i < size; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
