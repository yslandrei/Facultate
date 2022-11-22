#include <stdio.h>

int main(){
    int a, b;
    int *p = &a, *q = &b;
    scanf("%d %d", &a, &b);
    printf("%d\n", *p + *q);
}