#include <stdio.h>
#include <string.h>

void fibonacci(int a, int b, int i, int n){
    if(i == n)
        return;
    printf("%d ", b);
    fibonacci(b, a + b, i + 1, n);
}

int getInput(){
    char input[100];
    int isNumber, n = 0;
    printf("Introduceti cate numere Fibonacci vreti sa generati: ");
    do{
        
        fgets(input, sizeof(input), stdin);
        isNumber = 1;
        for(int i = 0; i < strlen(input) - 1; i ++)
            if(strchr("0123456789", input[i]) == NULL)
                isNumber = 0;
        if(input[0] == '-')
            printf("Eroare! Ati introdus un numar negativ: ");
        else if(isNumber == 0)
            printf("Eroare! Ati introdus un string: ");
        else if(strlen(input) - 1 > 9){
            printf("Eroare! Ati introdus un numar prea mare: ");
            isNumber = 0;
        }
    }while(!isNumber);
    for(int i = 0; i < strlen(input) - 1; i ++)
        n = n * 10 + (int)(input[i] - '0');
    return n;
}

int main(){
    int n;
    n = getInput();
    fibonacci(0, 1, 0, n);
    printf("\n");
}