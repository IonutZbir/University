#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node{
    char* val; // da fare con object
    struct node *next;
};
typedef struct node node;


struct linked_list{
    node *pointer; // punta al primo elemento della sequenza
    int len; // lunghezza lista
};
typedef struct linked_list linked_list;

linked_list init(void);
linked_list in0(linked_list, char*);
linked_list del0(linked_list);
linked_list insert(linked_list, int, char*);
linked_list delete(linked_list, int);
node *search(linked_list, int);
void print_llist(linked_list);



void main(int dim, char *args[]){ // dim e la dimensione di args
    linked_list L = init();

    L = insert(L, 0, "programmazione");
    L = insert(L, 1, "dei");
    L = insert(L, 2, "calcolatori");
    L = insert(L, L.len-1, "python e C");

    print_llist(L);
    printf("\n--------------\n");
    L = delete(L, 1);
    print_llist(L);

    for(int i = 0; i < dim; i++){
        printf("%s\n", args[i]);
    }
}

linked_list init(void){
    linked_list l = {NULL, 0};
    return l;
}

linked_list in0(linked_list list, char* elem){
    node *p = malloc(sizeof(node));
    p->val = malloc(strlen(elem) + 1 * sizeof(char));
    p->val = strcpy(p->val, elem); 
    p->next = list.pointer;
    list.pointer = p;
    list.len++;
    return list;
}

linked_list del0(linked_list list){
    node *p = list.pointer;
    list.pointer = p->next;
    free(p->val);
    free(p);
    list.len--;
    return list;
}

node *search(linked_list list, int pos){
    // restituisce il puntatore del node in posizione pos, NULL se la posizione pos non esiste
    node *p = list.pointer;
    int i = 0;
    while(p != NULL && i < pos){
        // if(pos == 0)
        //     return list.pointer;
        // else if (pos == i)
        //     return p;
        p = p->next;
        i++;
    }
    return p;
}

linked_list insert(linked_list list, int pos, char* elem){
    node *pre_node, *p;
    if(pos > 0 && pos <= list.len){ // <= se aggiungo alla fine della lista
        pre_node = search(list, pos - 1);
        p = malloc(sizeof(node));
        p->val = malloc(strlen(elem) + 1 * sizeof(char));
        p->val = strcpy(p->val, elem);
        p->next = pre_node->next;
        pre_node->next = p;
        list.len++; 
    }else if(pos == 0){
        list = in0(list, elem);
    }
    return list;
}

linked_list delete(linked_list list, int pos){
    node *pre_node, *pos_node;
    if(pos > 0 && pos < list.len){    
        pre_node = search(list, pos - 1);
        pos_node = pre_node->next;
        pre_node->next = pos_node->next;
        free(pos_node->val);
        free(pos_node);
        list.len--;
    }else if(pos == 0 && list.len > 0){
        list = del0(list);
    }

    return list;
}

void print_llist(linked_list list){
    node *p = list.pointer;
    while(p != NULL){
        printf("%s\n", p->val);
        p = p->next; // uquivalente a p = (*p).next
    }
}