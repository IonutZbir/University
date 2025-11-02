#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item_dict{
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
    node **arr;
    int len;
    int cap; 
};
typedef struct dict dict;

dict init_dict(int);
dict dict_resize(dict, int);
dict dict_set(dict, item_dict);
int dict_del(dict, char*);
node* dict_search(dict, char*);
node* in0(node*, item_dict);
int hash(dict, char*);
void print_llist(node*);
void print_dict(dict);


void main(int dim, char* args[]){
    dict d = init_dict(3);
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

/*
*   Funzione hash
*   ritorna un indice del dizionario
*/

int hash(dict d, char* key){
    /*
    Operatori bit-a-bit
    ^ : xor
    & : and
    | : or
    */
    int i = 0, hash_val = 0;
    while(key[i] != '\0'){
        hash_val = hash_val ^ key[i];
        i++;
    }
    return hash_val % d.cap;
}

dict dict_set(dict d, item_dict elem){
    node *nd;
    int p = hash(d, elem.key);
    nd = dict_search(d, elem.key);
    if(nd != NULL){
        nd->info.val = elem.val;
    }else{
        d.arr[p] = in0(d.arr[p], elem);
        d.len++;
    }
    if((d.len / d.cap) > 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

// elimina dall dizionario l elemento con chiave key(se esiste)
// restituisce 1 se key è una chiave

int dict_del(dict d, char *key){
    int p = hash(d, key);
    node *nd = dict_search(d, key);
    if(nd == NULL){
        return 0;
    }
    if(d.arr[p] == nd){ // cancellazione dalla testa della lista
        d.arr[p] = nd->next;
    }
    else{ // cancellazione all' interno della lista
        node *nd_pre = d.arr[p];
        while(nd_pre != nd){
            nd_pre = nd_pre->next;
        }
        nd_pre->next = nd->next;
    }
    free(nd);
    d.len--;
    return 1;
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


// void print_dict(dict d){
//     printf("dict = { ");
//     for(int i = 0; i < d.cap; i++){
//         print_llist(d.arr[i]);
//     }
//     printf("}\n");
// }

// void print_llist(node* nd){
//     node *p = nd;
//     while(p != NULL){
//         printf("\"%s\": %f; ",p->info.key, p->info.val);
//         p = p->next; // uquivalente a p = (*p).next
//     }
// }

void print_dict(dict d){
	int i;
	for (i = 0; i < d.cap; i++){
        printf("%d: ", i);
		print_llist(d.arr[i]);
		printf("\n");
	}
}

void print_llist(node *nd){
	node *p = nd;
	
	while( p != NULL ){
		printf("(\"%s\", %f) ", p->info.key, p->info.val);
		p = p->next; /*equivalente a p = (*p).next */
	}
}

dict dict_resize(dict old_d, int new_cap){
    dict new_d = init_dict(new_cap);
    node *nd;
    for(int i = 0; i < old_d.cap; i++){
        while(old_d.arr[i] != NULL){
            nd = old_d.arr[i];
            dict_set(new_d, nd->info); // cancello il primo nodo
            old_d.arr[i] = nd->next;
            free(nd);
        }
    }
    free(old_d.arr);
    return new_d;
}