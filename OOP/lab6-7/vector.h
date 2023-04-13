#include <stdlib.h>
#include "offer.h"

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

    T* begin() noexcept {
        return arr;
    }

    T* end() noexcept {
        return arr + currSize;
    }

    const int size() const {
        return currSize;
    }

    T& operator[](int index) {
        return arr[index];
    }

    const T& operator[](int index) const noexcept {
        return arr[index];
    }

    vector& operator=(const vector& other) {
        if (this != &other) {
            delete[] arr;
            currSize = other.currSize;
            maxSize = other.maxSize;
            arr = new T[maxSize];
            for (int i = 0; i < currSize; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
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

};


