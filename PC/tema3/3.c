#include <stdio.h>

float reciprocal(int nr){
    return 1.0 / nr;
}

float square(int nr){
    return nr * nr;
}

void performtask(int st, int dr, float (*f)(int)){
    for(int i = st; i <= dr; i ++)
        printf("%f ", (*f)(i));
    printf("\n");
}

int main(){
    performtask(1, 5, reciprocal);
    performtask(1, 5, square);
}