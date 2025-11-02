#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node{
    float val; // da fare con object
    struct node *next;
};
typedef struct node node;


struct linked_list{
    node *pointer; // punta al primo elemento della sequenza
    int len; // lunghezza lista
};
typedef struct linked_list linked_list;

linked_list init(void);
linked_list in0(linked_list, float);
linked_list del0(linked_list);
linked_list insert(linked_list, int, float);
linked_list delete(linked_list, int);
node *search(linked_list, int);
void print_llist(linked_list);



void main(){
    linked_list L = init();
    for(int i = 0; i < 10; i++){
        L = in0(L, i + 1 * 10);
    }
    L = insert(L, 1, 1);
    L = insert(L, 3, 6);
    L = insert(L, L.len, L.len);
    L = insert(L, 0, 12);

    print_llist(L);
    printf("\n\n------------------------------\n\n");

    L = delete(L, 0);
    L = delete(L, L.len-1);
    L = delete(L, 6);
    L = delete(L, 90);

    print_llist(L);
}

linked_list init(void){
    linked_list l = {NULL, 0};
    return l;
}

linked_list in0(linked_list list, float elem){
    node *p = malloc(sizeof(node));
    p->val = elem;
    p->next = list.pointer;
    list.pointer = p;
    list.len++;
    return list;
}

linked_list del0(linked_list list){
    node *p = list.pointer;
    list.pointer = p->next;
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

linked_list insert(linked_list list, int pos, float elem){
    node *pre_node, *p;
    if(pos > 0 && pos <= list.len){ // <= se aggiungo alla fine della lista
        pre_node = search(list, pos - 1);
        p = malloc(sizeof(node));
        p->val = elem;
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
        printf("%f\n", p->val);
        p = p->next; // uquivalente a p = (*p).next
    }
}