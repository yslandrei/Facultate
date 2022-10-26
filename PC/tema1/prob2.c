#include <stdio.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a + b);
    printf("%f\n", (float)(a + b) / 2);
    printf("%d\n", a * a + b * b);
}