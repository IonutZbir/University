#include <stdio.h>
#include <stdlib.h>

void print_arr(int arr[], int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}


int *copy_arr(int *arr, int len) // equivalente ad arr[]
{                                           
    int *new_arr = malloc(len * sizeof(int)); // allocare memoria al di fuori del frame della funzione
    // prende in input il numero di byte consecutivi che ci servono e
    // restituisce l' indirizzo del primo byte (nr. elem * nr. byte di un tipo)
    if (new_arr != NULL) // se malloc va a fallire ad allocare la memoria
    {
        for (int i = 0; i < len; i++)
        {
            new_arr[i] = arr[i];
        }
    }
    return new_arr;
}

// una funzione che prende un array e un elemento e gli aggiungi un elemento alla fine

int *append_arr(int *arr, int len, int elem)
{                                           
    int *new_arr = malloc((len + 1) * sizeof(int));
    if (new_arr != NULL)
    {
        for (int i = 0; i < len; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[len] = elem;
    }
    return new_arr;
}



void main()
{
    int a [] = {1, 2, 3, 4, 5};
    int b [] = {6, 7, 8, 9, 10};
    int len_a = sizeof(a) / sizeof(int);
    int len_b = sizeof(b) / sizeof(int);
    int *p;
    p = copy_arr(a, len_a);
    if(p != NULL)
        print_arr(p, len_a);
    else
        printf("Errore nell'allocazione della memoria");
    
    free(p);
    p = append_arr(b, len_b, 50);
    int len_p = len_b + 1;
    if(p != NULL)
        print_arr(p, len_p);
    else
        printf("Errore nell'allocazione della memoria");
    
    printf("%ld\n", sizeof(long));
    
}