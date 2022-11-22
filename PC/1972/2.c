#include<stdio.h>

int v[10000];

void quick_sort(int st,int dr){
    if(st<dr){
        int  m=(st+dr)/2,d;
        int i,j,aux;
        aux=v[st];
        v[st]=v[m];
        v[m]=aux;
        i=st;
        j=dr;
        d=0;
        while(i<j){
            if(v[i]>v[j]){
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
            d = 1-d;
            }
        i=i+d;
        j-=1-d;
        }
    quick_sort(i+1,dr);
    quick_sort(st,i-1);
    }
}

int main(){
    int i,n;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
	    scanf("%d",&v[i]);
    quick_sort(1,n);
    for(i=1;i<=n;i++)
        printf("%d ",v[i]);
    return 0;
}