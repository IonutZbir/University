#include <stdio.h>

void change_array(int x[], int len){
    
    for(int i = 0; i<len; i++){
        x[i] = i*10;
    }
    //printf("**********%d\n", sizeof(x)/sizeof(int)); // dentro x c'e l indirizzo e il tipo, e un puntatore
    //la dimensione di un puntatore e di 8 byte
    //se devo fare un funzione che modifica tutti gli elementi di un array, gli devo passare la dimensione
}

void main(){
    // Array
    int a[10]; // il nome di un array rappresenta l indirizzo del primo elemento dell array 
    int b[] = {1, 2, 4, 5, 12, 23, 45};
    int c[15] = {1, 2, 3, 4}; // da 4 in poi sono tutti 0
    int d[100] = {0}; // tutti 0
    int len_c = sizeof(c)/sizeof(int); // l accesso in lettura richiede tempo costante, anche in python
    for(int i = 0; i<len_c; i++){
        printf("%d\n", c[i]);
    }
    // un array è rappresentato da un indirizzo di memoria e da un tipo
    printf("............................");
    change_array(c, len_c);
    for(int i = 0; i<len_c; i++){
        printf("%d\n", c[i]);
    }
}

