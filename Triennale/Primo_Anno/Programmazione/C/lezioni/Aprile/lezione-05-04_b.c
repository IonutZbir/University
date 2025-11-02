#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct object{
    char type; // 'i', 'c', 's' per int, char e string
    void *pointer;
};

typedef struct object object;

void set(object*, int, object);

void main(){
    object lista[10];
    char a[] = "programmzione";
    lista[0].pointer = malloc(sizeof(int));
    lista[0].type = 'i';
    *( (int*) lista[0].pointer) = 3; // *() operatore, (int*) casting del tipo

    
    int *p;
    lista[0].pointer = 3;



    lista[1].pointer = malloc(sizeof(char));
    lista[1].type = 'c';
    *( (char*) lista[1].pointer) = 'x';

    lista[2].pointer = (void *)a; //assegno a lista[2] il puntatore che punta alla stringa a
    lista[2].type = 's';

    printf("[");
    for(int i = 0; i < 3; i++){
        if(lista[i].type == 'i')
            printf("%d ", *((int*)lista[i].pointer));
        if(lista[i].type == 'c')
            printf("%c ", *((char*)lista[i].pointer));
        if(lista[i].type == 's')
            printf("%s ", ((char *)lista[i].pointer));
    }
    printf("]\n");

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