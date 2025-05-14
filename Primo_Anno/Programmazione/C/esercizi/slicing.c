#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions/linked_list.h"

linked_list slice(linked_list, int, int);

void main(int dim, char *args[])
{
    int dati[] = {1, 2, 3, 4};
    linked_list list = ll_init();
    for (int i = 0; i < 4; i++)
    {
        list = ll_append_int(list, dati[i]);
    }
    list = ll_append_float(list, 6.4);
    list = ll_append_char(list, 'c');
    list = ll_append_string(list, "Sono una Stringa");
    ll_print(list);
    list = slice(list, 2, list.len);
    ll_print(list);
}

linked_list slice(linked_list list, int i, int j){
    linked_list sub_list = ll_init();
    node *nd = ll_search(list, i);
    int pos = i, c = 0;
    char type;
    if(j == 0 || j > list.len)
    {
        j = list.len + 1;
    }
    if(i > list.len || i >= j){
        return sub_list;
    }
    while (nd != NULL && pos < j) // O(j - i)
    {
        type = nd->data.type;
        switch (type)
        {
            case INT:
                sub_list = ll_append_int(sub_list, (*(int *)nd->data.val));
                break;
            case FLOAT:
                sub_list = ll_append_float(sub_list, (*(float *)nd->data.val));
                break;
            case LONG:
                sub_list = ll_append_long(sub_list, (*(long *)nd->data.val));
                break;
            case DOUBLE:
                sub_list = ll_append_double(sub_list, (*(double *)nd->data.val));
                break;
            case CHAR:
                sub_list = ll_append_char(sub_list, (*(char *)nd->data.val));
                break;
            case STRING:
                sub_list = ll_append_string(sub_list, nd->data.val);
                break;
            default:
                break;
        }
        pos++;
        c++;
        nd = nd->next;
    }
    return sub_list;
}