#include <stdio.h>
#include <stdlib.h>

/*
    a = [1, 3, 5, 6, 7, 5, 3]
                  3  
    porzione(3, 5) = [6, 7]
    i = 3
*/

struct nodo
{
    int inf;
    struct nodo *succ;
};
typedef struct nodo nodo;

struct l_list{
    nodo *head;
    int len;
};
typedef struct l_list l_list; 

nodo *ll_search(l_list list, int pos)
{
    // TODO: binary search
    nodo *nd = list.head;
    int i = 0;
    while (nd != NULL && i < pos)
    {
        nd = nd->succ;
        i++;
    }
    return nd;
}

l_list in0(l_list list, float elem){
    nodo *p = malloc(sizeof(nodo));
    p->inf = elem;
    p->succ = list.head;
    list.head = p;
    list.len++;
    return list;
}

l_list insert(l_list list, int pos, int elem){
    nodo *pre_node, *p;
    if(pos > 0 && pos <= list.len){ // <= se aggiungo alla fine della lista
        pre_node = ll_search(list, pos - 1);
        p = malloc(sizeof(nodo));
        p->inf = elem;
        p->succ = pre_node->succ;
        pre_node->succ = p;
        list.len++; 
    }else if(pos == 0){
        list = in0(list, elem);
    }
    return list;
}

void print_llist(l_list list){
    nodo *p = list.head;
    while(p != NULL){
        printf("%d\n", p->inf);
        p = p->succ; // uquivalente a p = (*p).next
    }
}

l_list slicing(l_list ll, int i, int j){
    l_list sub_ll = {NULL, 0};
    nodo *nd = ll_search(ll, i);
    if(j == 0 || j > ll.len)
    {
        j = ll.len + 1;
    }
    if(i > ll.len || i >= j){
        return sub_ll;
    }
    int pos = i, c = 0;
    while (nd != NULL && pos < j) // O(j - i)
    {
        sub_ll = insert(sub_ll, c, nd->inf);
        pos++;
        c++;
        nd = nd->succ;
    }
    return sub_ll;
}

void main(){
    l_list ll = {NULL, 0};
    for(int i = 0; i < 10; i++){
        ll = insert(ll, i, i*2 + 1);
    }

    l_list sub_ll = slicing(ll, 1, 12312);

    print_llist(ll);
    printf("\n\n");
    print_llist(sub_ll);
    // printf("\n\n");
    // print_llist(ll);
}