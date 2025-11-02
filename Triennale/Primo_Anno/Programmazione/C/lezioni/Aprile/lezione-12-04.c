#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct object{
    char type; // 'i', 'c', 's' per int, char e string
    void *pointer;
};

typedef struct object object;

struct list{
    object *arr;
    int len;
};

typedef struct list list;

void set(object*, int, object);
object new_int(int);
object new_char(char);
object new_string_alias(char *);
object new_string_clone(char *);
void print_list(list);



void main(){
    list lista = {NULL, 10};
    lista.arr = malloc(sizeof(object) * lista.len);
    char a[] = "programmzione";
    lista.arr[0] = new_int(4);
    lista.arr[1] = new_char('g');
    lista.arr[2] = new_string_clone(a);
    lista.arr[3] = new_string_alias("ciao");
    a[0] = 'P';

    print_list(lista);
}


void set(object *lista , int pos, object element){
    lista[pos].type = element.type;
    if(lista[pos].type == 'i'){
        lista[pos].pointer = malloc(sizeof(int));
        *( (int*) lista[pos].pointer) = *((int*)element.pointer);
    }
    if(lista[pos].type == 'c'){
        lista[pos].pointer = malloc(sizeof(char));
        *( (char*) lista[pos].pointer) = *((char*)element.pointer);
    }
    if(lista[pos].type == 's'){
        lista[pos].pointer = malloc(sizeof(char) * strlen((char*)element.pointer) + 1);
        strcpy(element.pointer, lista[pos].pointer);
    }
    lista[pos].pointer = element.pointer;

}

object new_int(int val){
    object out = {'i', NULL};
    out.pointer = malloc(sizeof(int));
    *((int *)out.pointer) = val;
    return out;
}

object new_char(char val){
    object out = {'c', NULL};
    out.pointer = malloc(sizeof(char));
    *((char *)out.pointer) = val;
    return out;
}

object new_string_alias(char *val){
    object out = {'s', NULL};
    out.pointer = val; // out.pointer è un alias, time complexity e spaziale O(1)
    /*
    out.pointer = malloc(sizeof(char));
    *((char *)out.pointer) = val;
    */
    return out;
}

object new_string_clone(char *val){
    object out = {'s', NULL}; // out.pointer contiene una copia, complessità temporale e spaziale O(n)
    out.pointer = malloc(sizeof(char) * (strlen(val) + 1));
    out.pointer = (out.pointer, val);
    return out;
}

void print_list(list lista){
    printf("[");
    for(int i = 0; i < lista.len; i++){
        if(lista.arr[i].type == 'i')
            printf("%d, ", *((int*)lista.arr[i].pointer));
        if(lista.arr[i].type == 'c')
            printf("%c, ", *((char*)lista.arr[i].pointer));
        if(lista.arr[i].type == 's')
            printf("%s, ", ((char *)lista.arr[i].pointer));
    }
    printf("]\n");
}