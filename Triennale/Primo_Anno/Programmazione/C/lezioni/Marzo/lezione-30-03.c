#include <stdio.h>
#include <stdlib.h>

struct array_int
{
  int *array; //puntatore dell array
  int len; // nr elementi array
  int capacity;
};
typedef struct array_int array_int;
array_int array_int_init(void);
array_int array_int_append(array_int, int);
array_int array_int_insert(array_int, int, int);
array_int array_int_pop(array_int);
array_int find_spaces(char *);
void array_int_print(array_int);

void main(){  
    char str[] = "ciao mondo ddas dadsa dasa dsd ";
    array_int spaces = find_spaces(str);
    array_int_print(spaces);
    printf("len -> %d, cap -> %d\n", spaces.len, spaces.capacity);
}


array_int array_int_init(void){  //O(1)
  array_int v = {NULL, 0, 0};
  return v;
}

array_int array_int_append(array_int old_arr, int elem){ // O(arr.len)
    
    int i;
    int *new_arr;
    if(old_arr.len == old_arr.capacity){
        new_arr = malloc((2 * old_arr.capacity + 1) * sizeof(int));
        if(new_arr == NULL)
            return old_arr;
    
        for (i = 0; i < old_arr.len; i++)
        {
            new_arr[i] = old_arr.array[i];
        }
        old_arr.capacity = 2*(old_arr.capacity + 1);
        free(old_arr.array); // libero lo spazio di memoria in cui era allocato il vecchio array
        old_arr.array = new_arr; // assegno al puntatore il nuovo array
    }
    old_arr.array[old_arr.len] = elem;
    old_arr.len++;

    return old_arr;
    /*
        Complessità temporale è O(1) nel caso medio (n append consecutivi costano O(n))
        Complessità spaziale è O(n) perché neò caso peggiore viene usata la metà della memoria allocata
    */


}

array_int array_int_insert(array_int arr, int pos, int elem){
    int old_cap = arr.capacity, old_len = arr.len;

    if(pos > arr.len){
        return arr;
    }

    arr = array_int_append(arr, 0);
    if (old_cap == old_len && old_cap == arr.capacity){ // malloc dentro append ritorna NULL
        return arr;
    }

    int i;
    for(i = arr.len - 1; i >= pos; i--){
        arr.array[i + 1] = arr.array[i];
    }
    arr.array[pos] = elem;
    return arr;
}

array_int array_int_pop(array_int arr){
    if(arr.len > 0){
        arr.len--;
    }
    return arr;
}


array_int find_spaces(char *str){
    //La funzione riceve in input una stringa
    //restituisce un array_int contenente le posizioni degli spazi in str
    int i = 0;
    array_int arr_spaces = array_int_init();
    while(str[i] != '\0'){
        if(str[i] == ' '){
            arr_spaces = array_int_append(arr_spaces, i);
        }
        i++;
    }
    return arr_spaces;
}


void array_int_print(array_int arr){ // O(arr.len)
    printf("["); 
    int i;
    for(i = 0; i < arr.len - 1; i++){
        printf("%d, ", arr.array[i]);
    }
    printf("%d]\n", arr.array[i]);
}