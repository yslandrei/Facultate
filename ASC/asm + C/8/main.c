#include <stdio.h>

void printBase8(int);

void printAscii(int);

int main(){
    for(int i = 32; i <= 126; i ++){
        printf("%d: ", i);
        printBase8(i);
        printf(" ");
        printAscii(i);
        printf("\n");
    }
    return 0;   
}