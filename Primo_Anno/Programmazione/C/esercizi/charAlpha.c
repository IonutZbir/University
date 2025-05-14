#include <stdio.h>

void printAlphaChar(){
    char min, masc;
    int diff = 'a' - 'A';
    for(min = 'a'; min <= 'z'; min++){
        masc = min - diff;
        printf("%c, %d | %c, %d\n", min, min, masc, masc);
    }
}

void main(){
    printf("Minuscolo | Maiuscolo\n");
    printAlphaChar();
}