#include <stdio.h>

int combinari(int n, int k) {
    int p = 1;
    for (int i = 1; i <= k; i++)
        p = p * (n - i + 1) / i;

    return p;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        printf("%d ", combinari(n - 1, i));
    return 0;
}