#include <stdio.h>

int factorial(int x){
    if(x < 0)
        return 0;
    int fact;
    for(fact = 1; x > 0; x --)
        fact = fact * x;
    return fact;
}

int main(){
    int factorial(int n);
    printf("Value of n, and n!\n\n");
    for(int i = 0; i <= 5; i ++)
        printf(" %2d    %4d\n", i, factorial(i));
    return 0;
}