#include <stdio.h>

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

int partition(int array[], int l, int r){
    int pi = array[r];
    int i = l - 1;
    for(int j = l; j < r; j ++){
        if(array[j] <= pi){
            i ++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[r]);
    return (i + 1);
}

void quickSort(int array[], int l, int r){
    if(l < r){
        int pi = partition(array, l, r);
        quickSort(array, pi + 1, r);
        quickSort(array, l, pi - 1);
    }
}

void printArray(int array[], int n){
    for(int i = 0; i < n; i ++)
        printf("%d ", array[i]);
    printf("\n");
}

int main(){
    int array[] = {8, 7, 1, 3, 5, 4, 2, 6};
    int n = sizeof(array) / sizeof(array[0]);
    printf("Unsorted Array:\n");
    printArray(array, n);
    printf("Sorted Array:\n");
    quickSort(array, 0, n - 1);
    printArray(array, n);

}