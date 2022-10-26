#include <stdio.h>

int main(){
    char ch[10] = "abcdefghi";
    int vowels = 0, nonvowels = 0;
    for(int i = 0; i < 10; i ++)
        switch(ch[i]){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u': 
                vowels ++;
                break;
            default: 
                nonvowels ++;
                break;
        }
    printf("vocale: %d\nconsoane: %d\n", vowels, nonvowels);
}