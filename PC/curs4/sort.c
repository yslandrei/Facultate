#include <stdio.h>

int sort(int arr[], int size){
    int aux;
    for(int i = 0; i < size; i ++)
        for(int j = i; j > 0; j --)
            if(arr[j] < arr[j - 1]){
                (arr[j] ^= arr[j - 1] ^= arr[j] ^= arr[j - 1]);
                /*aux = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = aux;*/
            }
}

int main(){
    int arr[10] = {5, 4, 3, 2, 6, 8, 7, 9, 1, 0};
    int size = 10;
    printf("Initial Array: ");
    for(int i = 0; i < size; i ++)
        printf("%d ", arr[i]);
    sort(arr, size);
    printf("\nSorted Array: ");
    for(int i = 0; i < size; i ++)
        printf("%d ", arr[i]);
    printf("\n");
}