#include <stdio.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    printf("Sum of Numbers: %d\n", a + b);
    printf("Average of Numbers: %f\n", (float)(a + b) / 2);
    printf("Sum of Squared Numbers: %d\n", a * a + b * b);
}