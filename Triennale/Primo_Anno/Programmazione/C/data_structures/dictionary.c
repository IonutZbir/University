#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"


// initialize the dictionary
dict dict_init(int cap){
    dict d;
    d.head = malloc(sizeof(d_node*) * cap);
    d.len = 0;
    d.cap = cap;
    for (int i = 0; i < d.cap; i++)
    {
        d.head[i] = NULL;
    }
    return d;
}

int hash(dict d, char* key){
    /*
    Funzione di hash delle chiave
    */
    int i = 0, hash_val = 0;
    while(key[i] != '\0'){
        hash_val = hash_val ^ key[i];
        i++;
    }
    return hash_val % d.cap;
}

// Insert or Update the dictionary with int value
dict dict_set_int(dict d, char* key, int value){
    d_node *nd, nd_to_insert;
    object obj;
    int index_dict = hash(d, key);
    char curr_type;
    nd = dict_search(d, key);
    if(nd != NULL){
        *(int *)nd->data.val = value;
        nd->data.type = INT;
    }else{
        obj.type = INT;
        obj.val = malloc(sizeof(int));
        *(int *)obj.val = value;
        nd_to_insert.data = obj;
        nd_to_insert.key = key;
        d.head[index_dict] = dict_in0(d.head[index_dict], nd_to_insert);
        d.len++;
    }
    if((d.len / d.cap) >= 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

// Insert or Update the dictionary with float value
dict dict_set_float(dict d, char* key, float value){
    d_node *nd, nd_to_insert;
    object obj;
    int index_dict = hash(d, key);
    char curr_type;
    nd = dict_search(d, key);
    if(nd != NULL){
        *(float *)nd->data.val = value;
        nd->data.type = FLOAT;
    }else{
        obj.type = FLOAT;
        obj.val = malloc(sizeof(float));
        *(float *)obj.val = value;
        nd_to_insert.data = obj;
        nd_to_insert.key = key;
        d.head[index_dict] = dict_in0(d.head[index_dict], nd_to_insert);
        d.len++;
    }
    if((d.len / d.cap) >= 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

// Insert or Update the dictionary with long value
dict dict_set_long(dict d, char* key, long value){
    d_node *nd, nd_to_insert;
    object obj;
    int index_dict = hash(d, key);
    char curr_type;
    nd = dict_search(d, key);
    if(nd != NULL){
        *(long *)nd->data.val = value;
        nd->data.type = LONG;
    }else{
        obj.type = LONG;
        obj.val = malloc(sizeof(long));
        *(long *)obj.val = value;
        nd_to_insert.data = obj;
        nd_to_insert.key = key;
        d.head[index_dict] = dict_in0(d.head[index_dict], nd_to_insert);
        d.len++;
    }
    if((d.len / d.cap) >= 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

// Insert or Update the dictionary with double value
dict dict_set_double(dict d, char* key, double value){
    d_node *nd, nd_to_insert;
    object obj;
    int index_dict = hash(d, key);
    char curr_type;
    nd = dict_search(d, key);
    if(nd != NULL){
        *(double *)nd->data.val = value;
        nd->data.type = DOUBLE;
    }else{
        obj.type = DOUBLE;
        obj.val = malloc(sizeof(double));
        *(double *)obj.val = value;
        nd_to_insert.data = obj;
        nd_to_insert.key = key;
        d.head[index_dict] = dict_in0(d.head[index_dict], nd_to_insert);
        d.len++;
    }
    if((d.len / d.cap) >= 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

// Insert or Update the dictionary with char value
dict dict_set_char(dict d, char* key, char value){
    d_node *nd, nd_to_insert;
    object obj;
    int index_dict = hash(d, key);
    char curr_type;
    nd = dict_search(d, key);
    if(nd != NULL){
        *(char *)nd->data.val = value;
        nd->data.type = CHAR;
    }else{
        obj.type = CHAR;
        obj.val = malloc(sizeof(char));
        *(char *)obj.val = value;
        nd_to_insert.data = obj;
        nd_to_insert.key = key;
        d.head[index_dict] = dict_in0(d.head[index_dict], nd_to_insert);
        d.len++;
    }
    if((d.len / d.cap) >= 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

// Insert or Update the dictionary with string value
dict dict_set_string(dict d, char* key, char* value){
    d_node *nd, nd_to_insert;
    object obj;
    int index_dict = hash(d, key);
    char curr_type;
    nd = dict_search(d, key);
    if(nd != NULL){
        nd->data.val = malloc(sizeof(char) * strlen(value) + 1);
        nd->data.val = strcpy(nd->data.val, value);
        nd->data.type = STRING;
    }else{
        obj.type = STRING;
        obj.val = malloc(sizeof(char) * strlen(value) + 1);
        obj.val = strcpy(obj.val, value);
        nd_to_insert.data = obj;
        nd_to_insert.key = key;
        d.head[index_dict] = dict_in0(d.head[index_dict], nd_to_insert);
        d.len++;
    }
    if((d.len / d.cap) >= 4){
        // ridimensiona il dizionario
        d = dict_resize(d, d.cap * 2 + 1);
    }
    return d;
}

int dict_del(dict d, char *key){
    /*
    Cancellazione dal dizionario
    */
    int index_dict = hash(d, key);
    d_node *nd = dict_search(d, key);
    if(nd == NULL){
        return 0;
    }
    if(d.head[index_dict] == nd){ // cancellazione dalla testa della lista
        d.head[index_dict] = nd->next;
    }
    else{ // cancellazione all' interno della lista
        d_node *nd_pre = d.head[index_dict];
        while(nd_pre != nd){
            nd_pre = nd_pre->next;
        }
        nd_pre->next = nd->next;
    }
    free(nd);
    d.len--;
    return 1;
}

d_node* dict_in0(d_node *nd, d_node nd_to_insert)
{
    /*
    Inserimento nel dizionario
    */
    d_node *p = malloc(sizeof(d_node));
    p->data = nd_to_insert.data;
    p->key = nd_to_insert.key;
    p->next = nd;
    nd = p;
    return nd;
}

d_node* dict_search(dict d, char *key){
    /*
    Ricerca nel dizionario
    */
    int index_dict = hash(d, key);
    d_node *q = d.head[index_dict];
    while (q != NULL && strcmp(q->key, key) != 0) // sono diverse
    {
        q = q->next;
    }
    return q;
}

dict dict_resize(dict old_d, int new_cap){
    /*
    Ridimensiona il dizionario
    */
    dict new_d = dict_init(new_cap);
    d_node *nd;
    char curr_type;
    for(int i = 0; i < old_d.cap; i++){
        while(old_d.head[i] != NULL){
            nd = old_d.head[i];
            curr_type = nd->data.type;
            switch (curr_type)
            {
            case INT:
                dict_set_int(new_d, nd->key, *(int *)nd->data.val);
                break;
            case FLOAT:
                dict_set_float(new_d, nd->key, *(float *)nd->data.val);
                break;
            case DOUBLE:
                dict_set_double(new_d, nd->key, *(double *)nd->data.val);
                break;
            case LONG:
                dict_set_long(new_d, nd->key, *(long *)nd->data.val);
                break;
            case CHAR:
                dict_set_char(new_d, nd->key, *(char *)nd->data.val);
                break;
            case STRING:
                dict_set_string(new_d, nd->key, nd->data.val);
                break;
            default:
                break;
            }
            old_d.head[i] = nd->next;
            // cancello il primo nodo
            free(nd);
        }
    }
    free(old_d.head);
    return new_d;
}

void dict_print(dict d){
    /*
    Stampa del dizionario: dict = {key: value;}
    */
    printf("dict = { ");
    for(int i = 0; i < d.cap; i++){
        llist_print(d.head[i]);
    }
    printf("}\n");
}

void llist_print(d_node* nd){
    char curr_type;
    
    while(nd != NULL){
        curr_type = nd->data.type;
            switch (curr_type)
            {
            case INT:
                printf("\"%s\": %d; ", nd->key, *(int *)nd->data.val);
                break;
            case FLOAT:
                printf("\"%s\": %f; ", nd->key, *(float *)nd->data.val);
                break;
            case DOUBLE:
                printf("\"%s\": %lf; ", nd->key, *(double *)nd->data.val);
                break;
            case LONG:
                printf("\"%s\": %ld; ", nd->key, *(long *)nd->data.val);
                break;
            case CHAR:
                printf("\"%s\": %c; ", nd->key, *(char *)nd->data.val);
                break;
            case STRING:
                printf("\"%s\": %s; ", nd->key, (char *)nd->data.val);
                break;
            default:
                break;
            }
        nd = nd->next; // uquivalente a p = (*p).next
    }
}

void dict_print_debug(dict d){
	int i;
	for (i = 0; i < d.cap; i++){
        printf("%d: ", i);
		llist_print_debug(d.head[i]);
		printf("\n");
	}
}

void llist_print_debug(d_node *nd){
	char curr_type;
	while( nd != NULL ){
        curr_type = nd->data.type;
            switch (curr_type)
            {
            case INT:
                printf("(\"%s\", %d) ", nd->key, *(int *)nd->data.val);
                break;
            case FLOAT:
                printf("(\"%s\", %f) ", nd->key, *(float *)nd->data.val);
                break;
            case DOUBLE:
                printf("(\"%s\", %lf) ", nd->key, *(double *)nd->data.val);
                break;
            case LONG:
                printf("(\"%s\", %ld) ", nd->key, *(long *)nd->data.val);
                break;
            case CHAR:
                printf("(\"%s\", %c) ", nd->key, *(char *)nd->data.val);
                break;
            case STRING:
                printf("(\"%s\", %s) ", nd->key, (char *)nd->data.val);
                break;
            default:
                break;
            }
		nd = nd->next; /*equivalente a p = (*p).next */
	}
}

// char **get_keys(dict d) {
//     if (d.len == 0) {
//         return NULL;
//     }

//     char **keys = malloc(sizeof(char *) * d.len);
//     int index = 0;

//     for (int i = 0; i < d.cap; i++) {
//         d_node *nd = d.arr[i];
//         while (nd != NULL) {
//             keys[index] = malloc(sizeof(char) * (strlen(nd->info.key) + 1));
//             strncpy(keys[index], nd->info.key, strlen(nd->info.key) + 1);
//             index++;
//             nd = nd->next;
//         }
//     }

//     return keys;
// }

// float* get_values(dict d){
//     /*
//     Restituisce un array di float contente tutti i valori del dizionario
//     */
//     if (d.len == 0) {
//         return NULL;
//     }

//     float *values = malloc(sizeof(float) * d.len);
//     int index = 0;

//     for (int i = 0; i < d.cap; i++) {
//         d_node *nd = d.arr[i];
//         while (nd != NULL) {
//             values[index] =  nd->info.val;
//             index++;
//             nd = nd->next;
//         }
//     }

//     return values;
// }