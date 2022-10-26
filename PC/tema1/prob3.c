#include <stdio.h>
#include <limits.h>

int main(){
    int minn = INT_MAX, maxx = INT_MIN, x;
    for(int i = 0; i < 5; i ++){
        scanf("%d", &x);
        if(x < minn)
            minn = x;
        if(x > maxx)
            maxx = x;
    }
    printf("Minmul: %d\nMaximul: %d\n", minn, maxx);
}