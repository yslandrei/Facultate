#include "vector.h"

template <typename T> vector<T>::vector() {
	arr = new T;
	size = 1;
	maxSize = 1;
}

template <typename T> vector<T>::~vector() {
	free(arr);
	size = 0;
	maxSize = 0;
}

template <typename T> void vector<T>::extendSize() {
	maxSize *= 2;
	T* tempArr = new T[maxSize];
	for (int i = 0; i < size; i++)
		tempArr[i] = arr[i];
	free(arr);
	arr = tempArr;
}