#include <stdio.h>

int getHundredsDigit(int);

int main(){
    int n, s1[100], s2[100];
    printf("Introduceti lungimea sirului: ");
    scanf("%d", &n);
    printf("Introduceti sirul: ");
    for(int i = 0; i < n; i ++){
        scanf("%d", &s1[i]);
        s2[i] = getHundredsDigit(s1[i]);
    }
    printf("\nCifrele sutelor ale numerelor din sir: ");
    for(int i = 0; i < n; i ++)
        printf("%d ", s2[i]);
}