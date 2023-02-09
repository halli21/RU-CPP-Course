#include <iostream>
#include <string.h>

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

void DynamicArray::remove(int index) {
    if (index >= size || index < 0) {
        std::cout << "Index out of range" << std::endl;
        return;
    }

    delete[] arr[index];

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;
}


DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    arr = new char*[capacity];

    for (int i = 0; i < size; i++) {
        arr[i] = new char[strlen(other.arr[i]) + 1];
        strcpy(arr[i], other.arr[i]);
    }
}


DynamicArray::~DynamicArray() {
        for (int i = 0; i < size; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
