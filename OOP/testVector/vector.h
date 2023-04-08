#include <stdlib.h>
#include <iostream>
#include "offer.h"

using std::cout;

template <typename T> class vector {
private:
    T* arr;
    int currSize;
    int maxSize;

    void extend() {
        maxSize *= 2;
        T* auxArr = new T[maxSize];
        for (int i = 0; i < currSize; i++)
            auxArr[i] = arr[i];
        delete[] arr;
        arr = auxArr;
    }

public:
    vector(int maxSize = 1) {
        arr = new T[maxSize];
        currSize = 0;
        this->maxSize = maxSize;
    }

    ~vector() {
        delete[] arr;
        currSize = 0;
        maxSize = 0;
    }

    T* begin() {
        return arr;
    }

    T* end() {
        return arr + currSize;
    }

    const int size() const {
        return currSize;
    }

    T& operator[](const int i) const {
        return arr[i];
    }

    void push_back(const T& newElem) {
        if (currSize == maxSize)
            extend();
        arr[currSize++] = newElem;
    }

    void erase(const T* oldElem) {
        int offset = 0;
        currSize--;
        for (int i = 0; i < currSize; i++) {
            if (arr[i] == *oldElem && offset == 0)
                offset++;
            arr[i] = arr[i + offset];
        }
    }

    void print() {
        for (int i = 0; i < currSize; i++) {
            cout << arr[i] << "\n";
        }
        cout << "\n";
    }

};


