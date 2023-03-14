#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int combinari(int n, int k) {
    int p = 1;
    for (int i = 1; i <= k; i++)
        p = p * (n - i + 1) / i;

    return p;
}

int main()
{
    /*
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        printf("%d ", combinari(n - 1, i));
    */

    int prec = 0;
    float nr = 0;
    printf("Introduceti numarul: ");
    cin >> nr;
    printf("Introduceti precizia: ");
    cin >> prec;
    
    cout << setprecision(prec) << (float)sqrt(nr);
    return 0;
}