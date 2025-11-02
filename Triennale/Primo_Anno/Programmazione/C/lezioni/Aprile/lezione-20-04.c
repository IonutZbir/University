#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item_dict{  // elemento del dizionario
    char *key;
    float val;
};
typedef struct item_dict item_dict;

struct node{
    item_dict info;
    struct node *next;
};
typedef struct node node;

struct dict{    
    node **arr; // array di puntatori a nodi
    int len;
    int cap; 
};
typedef struct dict dict;

dict init_dict(int);
dict dict_set(dict, item_dict);
node* dict_search(dict, char*);
node* in0(node*, item_dict elem);
int hash(dict, char*);
void print_llist(node*);
void print_dict(dict);


void main(int dim, char* args[]){
    dict d = init_dict(15);
    item_dict e;
    for (int i = 1; i < dim; i++)
    {
        //printf("%s ", args[i]);
        e.key = args[i];
        e.val = i;
        d = dict_set(d, e);
    }
    print_dict(d);
    
}

int hash(dict d, char* key){
    return 0;
}

dict dict_set(dict d, item_dict elem){
    node *nd;
    int p = hash(d, elem.key); // calcola la posizione del elemento all interno del dizionario
    nd = dict_search(d, elem.key); // cerco il nodo che corrisponde alla "key"
    if(nd != NULL){
        nd->info.val = elem.val; // il nodo con chiave key esiste, aggiorno solo il valore
    }else{
        d.arr[p] = in0(d.arr[p], elem); // il nodo con chiave "key" non esiste, aggiungo un nuovo nodo
        d.len++;
    }
    return d;
}

dict init_dict(int cap){
    dict d;
    d.arr = malloc(sizeof(node*) * cap);
    d.len = 0;
    d.cap = cap;
    for (int i = 0; i < d.cap; i++)
    {
        d.arr[i] = NULL;
    }
    return d;
}

node* dict_search(dict d, char *k){
    int p = hash(d, k);
    node *q = d.arr[p];
    while (q != NULL && strcmp(q->info.key, k) != 0) // sono diverse
    {
        q = q->next;
    }
    return q;
}

node* in0(node *nd, item_dict elem)
{
    node *p = malloc(sizeof(node));
    p->info = elem;
    p->next = nd;
    nd = p;
    return nd;
}

void print_dict(dict d){
    printf("dict = { ");
    for(int i = 0; i < d.cap; i++){
        print_llist(d.arr[i]);
    }
    printf("}\n");
}

void print_llist(node* nd){
    node *p = nd;
    while(p != NULL){
        printf("\"%s\": %f; ",p->info.key, p->info.val);
        p = p->next; // uquivalente a p = (*p).next
    }
}