#include <stdio.h>
#include <string.h>

int main(){
    int n = 0, fibNumb = 1, prevFibNumb = 0, aux;
    char input[100];
    int isNumber;
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

    for(int i = 1; i <= n; i ++){
        printf("%d ", fibNumb);
        aux = fibNumb;
        fibNumb += prevFibNumb;
        prevFibNumb = aux;
    }
    printf("\n");
}