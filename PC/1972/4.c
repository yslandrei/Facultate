#include <stdio.h>

int main(){
    int matrix[100][100], n, m, rowSum;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            scanf("%d", &matrix[i][j]);
    for(int i = 0; i < n; i ++){
        rowSum = 0;
        for(int j = 0; j < m; j ++)
            rowSum += matrix[i][j];
        printf("\nLinia %d: %d", i ,rowSum);
    }
}