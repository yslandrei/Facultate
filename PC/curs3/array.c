#include <stdio.h>
#define SIZE 100

int a[SIZE];

void print(int *x, int n){
    for(int i = 0; i < n; i ++)
        printf("%d ", x[i]);
    printf("\n");
}

int main(){
    int b[100] = {1};
    int c[100];
    int d[100];
    int i;
    for(i = 0; i < SIZE; i ++)
        d[i] = 1;
    print(a, SIZE);
    print(b, SIZE);
    print(c, SIZE);
    print(d, SIZE);
}