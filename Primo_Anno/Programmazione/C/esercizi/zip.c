#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/linked_list.h"


linked_list zip(linked_list l1, linked_list l2){
    linked_list lzip = ll_init();
    node *nd1 = l1.head, *nd2 = l2.head; 
    int i = 0;
    while (nd1 != NULL && nd2 != NULL)
    {
        strcat(nd1->data.val, " ");
        strcat(nd1->data.val, nd2->data.val);
        lzip = ll_insert_string(lzip, i, nd1->data.val);
        nd1 = nd1->next;
        nd2 = nd2->next;
        i++;    
    }
    return lzip;
    
}

void main(){
    char *d1[] = {"Ionut", "Francesco", "Mario"};
    char *d2[] = {"Alessandro", "Valerio", "Flavio", "Andrea"};
    linked_list l1 = ll_init();
    linked_list l2 = ll_init();
    for (int i = 0; i < 3; i++)
    {
        l1 = ll_insert_string(l1, i, d1[i]);
        l2 = ll_insert_string(l2, i, d2[i]);
    }
    ll_print(l1);
    ll_print(l2);

    linked_list l = zip(l1, l2);
    ll_print(l);
}