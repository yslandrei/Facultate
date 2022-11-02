#include <stdio.h>
#include <limits.h>

int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

int main(){
    const int size = 3;
    int matrix[100][100];
    int maxVal = INT_MIN;
    for(int r = 0; r < size; r ++)
        for(int c = 0; c < size; c ++){
            scanf("%d", &matrix[r][c]);
            maxVal = max(maxVal, matrix[r][c]);
        }
    printf("Valorea Maxima: %d\n", maxVal);
}