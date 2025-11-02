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

    char a[] = "                                                        ";
    array_int spaces = find_spaces(a);
    array_int_print(spaces);
    int i = 0;
    while (a[i] != '\0')
    {
        spaces = array_int_pop(spaces);
        array_int_print(spaces);
        printf("len -> %d, cap -> %d, index -> %d\n", spaces.len, spaces.capacity, i);
        i++;
    }
      
    
}


array_int array_int_init(void){  //O(1)
  array_int v = {NULL, 0, 0};
  return v;
}

// append with realloc

array_int array_int_append(array_int arr, int elem){ // O(arr.len)
    
    array_int old_arr = {arr.array, arr.len, arr.capacity};
    if(arr.len == arr.capacity){
        arr.array = realloc(arr.array, (2 * arr.capacity + 1) * sizeof(int));
        if(arr.array == NULL)
            return old_arr;
            
        arr.capacity = 2*(arr.capacity + 1);
    }
    arr.array[arr.len] = elem;
    arr.len++;
    free(old_arr.array);


    return arr;
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
        if(arr.len < arr.capacity / 4){
           arr.array = realloc(arr.array, (arr.capacity / 2 + 1) * sizeof(int)); // nel caso positivo, aumenta la capacita e costa tempo costante, altrimenti fa la malloc come gia fatto manualmente nella append
           arr.capacity = (arr.capacity / 2) + 1;
        }
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
