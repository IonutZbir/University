#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions/linked_list.h"

typedef struct point
{
    int x, y;
}point;

typedef struct triangle
{
    point po, p1, p2;
}triangle;

typedef struct paridispari {
    linked_list pari; 
    linked_list dispari;
}paridispari;

typedef struct coppialiste {
    linked_list testa;
    linked_list coda;
}coppialiste;

linked_list ll_insert_in_ordered_list_int(linked_list, int);
linked_list ll_insert_array_end_int(linked_list, int*, int);
linked_list ll_invert_list(linked_list);
linked_list StringSplit(char*, char);
linked_list merge_even_odd(linked_list, linked_list);
linked_list XstringaLista(char**, int);
linked_list SuccSum(linked_list);
linked_list PrecSum(linked_list);
paridispari PariDispari(linked_list);
coppialiste SpezzaLista(linked_list);
node *midlleNode(linked_list);
char *convert_to_bin(int, int);
int ContaRipetizioniIgnoraMaiuscolo(linked_list, char*);
float AreaTriangoloIsoscele(triangle);
void GeneraSeqBin(int);


void main(int dim, char *args[])
{
    int dati[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    linked_list list = ll_init();
    for (int i = 0; i < sizeof(dati)/sizeof(int); i++)
    {
        list = ll_append_int(list, dati[i]);
    }
    ll_print(list);
    node *middle;
    middle = midlleNode(list);
    printf("%d\n", *(int *)middle->data.val);
}

node *midlleNode(linked_list list){
    // node *slow = list.head, *fast = list.head;
    // while (fast != NULL && fast->next != NULL)
    // {
    //     slow = slow->next;
    //     fast = fast->next->next;
    // }
    // return slow;
    return ll_search(list, list.len / 2);
}

linked_list ll_insert_in_ordered_list_int(linked_list list, int value)
{
    int first = (*(int *)list.head->data.val);
    if (value <= first)
    {
        list = ll_insert_int(list, 0, value);
        return list;
    }
    node *nd = list.head->next;
    int i = 1, pos = 0;
    while (nd != NULL && i <= list.len && pos == 0)
    {
        if (value <= (*(int *)nd->data.val))
        {
            pos = i;
        }
        i++;
        nd = nd->next;
    }
    if (pos != i - 1)
        pos = i;
    list = ll_insert_int(list, pos, value);
    return list;

    // Costo Computazionale:
    // Caso Peggiore -> O(lista.len)
    // Caso Migliore -> O(1)
}

linked_list ll_insert_array_end_int(linked_list list, int *arr, int len_arr)
{
    linked_list newll = ll_init();
    for (int i = len_arr - 1; i >= 0; i--)
    {
        newll = ll_in0_int(newll, arr[i]);
    }
    ll_print(newll);
    node *last = ll_search(list, list.len - 1);
    last->next = newll.head;
    list.len += len_arr;
    return list;
}

linked_list ll_invert_list(linked_list list)
{
    node *prev = NULL;
    node *next = NULL;
    node *curr = list.head;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list.head = prev;
    return list;
}

int ContaRipetizioniIgnoraMaiuscolo(linked_list list, char *str_in)
{
    node *nd = list.head;
    int len_str_in = strlen(str_in), count = 0, count_tot = 0;
    while (nd != NULL)
    {
        if (nd->data.type != STRING)
            return 0;
        char *list_str = nd->data.val;
        if (strlen(list_str) == len_str_in)
        {
            for (int i = 0; i < len_str_in; i++)
            {
                if (list_str[i] == str_in[i] + 'a' - 'A' || list_str[i] == str_in[i] + 'A' - 'a' || list_str[i] == str_in[i])
                {
                    count += 1;
                }
            }
            if (count == len_str_in)
            {
                count_tot += 1;
            }
            count = 0;
        }
        nd = nd->next;
    }
    return count_tot;
}

linked_list StringSplit(char *str_in, char chrSpl)
{
    int len_str_in = strlen(str_in);
    linked_list list = ll_init();
    if (len_str_in == 0)
        return list;
    int pos = 0;
    char *newStr = malloc(sizeof(char));
    int j = 0;
    for (int i = 0; i < len_str_in; i++)
    {
        if (str_in[i] != chrSpl)
        {
            newStr[j] = str_in[i];
            j += 1;
            newStr = realloc(newStr, 1 + j);
        }
        else
        {
            newStr[j] = ' ';
            newStr[j + 1] = '\0';
            list = ll_insert_string(list, pos, newStr);
            pos += 1;
            j = 0;
            newStr[j] = '\0';
        }
    }
    list = ll_insert_string(list, pos, newStr);
    free(newStr);
    return list;
}

linked_list merge_even_odd(linked_list even, linked_list odd)
{
    // even: pari
    // odd: dispari
    linked_list merge = ll_init();
    node *nd_e = even.head;
    node *nd_o = odd.head;
    int i = 0;
    while (nd_e != NULL && nd_o != NULL)
    {
        if (*((int *)nd_e->data.val) < *((int *)nd_o->data.val))
        {
            merge = ll_insert_int(merge, i, *((int *)nd_e->data.val));
            nd_e = nd_e->next;
        }
        else
        {
            merge = ll_insert_int(merge, i, *((int *)nd_o->data.val));
            nd_o = nd_o->next;
        }
        i++;
    }
    while (nd_e != NULL)
    {
        merge = ll_insert_int(merge, i, *((int *)nd_e->data.val));
        nd_e = nd_e->next;
        i++;
    }
    while (nd_o != NULL)
    {
        merge = ll_insert_int(merge, i, *((int *)nd_o->data.val));
        nd_o = nd_o->next;
        i++;
    }
    return merge;
}

float AreaTriangoloIsoscele(triangle t){
    float d0, d1, d2, b, h, area;
    d0 = sqrt(pow(t.po.x - t.p1.x, 2) + pow(t.po.y - t.p1.y, 2));
    d1 = sqrt(pow(t.po.x - t.p2.x, 2) + pow(t.po.y - t.p2.y, 2));
    d2 = sqrt(pow(t.p1.x - t.p2.x, 2) + pow(t.p1.y - t.p2.y, 2));
    if (d0 == d1)
    {
        b = d2;
        h = sqrt(pow(d0, 2) - pow(b/2, 2));
        return (b * h)/2;
    }
    if (d0 == d2)
    {
        b = d1;
        h = sqrt(pow(d0, 2) - pow(b/2, 2));
        return (b * h)/2;
    }
    if (d1 == d2)
    {
        h = sqrt(pow(d1, 2) - pow(b/2, 2));
        b = d0;
        return (b * h)/2;
    }
    return -1;
}

paridispari PariDispari(linked_list list){
    node *nd = list.head;
    linked_list p = ll_init();
    linked_list d = ll_init();
    paridispari pd_s = {p, d};
    int i = 0, j = 0, val;
    while (nd != NULL)
    {
        val = *(int *)nd->data.val;
        if ((val % 2) == 0)
        {
            pd_s.pari = ll_insert_int(pd_s.pari, i, val);
            i++;
        }else{
            pd_s.dispari = ll_insert_int(pd_s.dispari, j, val);
            j++;
        }
        nd = nd->next;
    }
    return pd_s;
}

char *convert_to_bin(int number, int bits) {
    char *bin = malloc((bits + 1) * sizeof(char));
    int r;
    int i = bits - 1;
    while (number >= 0 && i >= 0) {
        r = number % 2;
        number = number / 2;
        if (r == 0) {
            bin[i] = '0';   
        } else {
            bin[i] = '1';
        }
        i--;
    }

    while (i >= 0) {
        bin[i] = '0';
        i--;
    }

    bin[bits] = '\0';
    return bin;
}


void GeneraSeqBin(int n){
    int n_seq = pow(2, n);
    char *bin;
    for (int i = 0; i < n_seq; i++)
    {
        printf("%s: %d\n", convert_to_bin(i, n), i);        
        free(bin);
    }
}

linked_list XstringaLista(char **arr, int len){
    linked_list list = ll_init();
    for (int i = 0; i < len; i++)
    {
        list = ll_insert_string(list, i, arr[i]);
    }
    return list;
}

linked_list SuccSum(linked_list list){
    int i = 0, sum;
    node *nd = list.head->next;
    while (i < list.len - 2)
    {   
        sum = *(int*)nd->data.val + *(int*)nd->next->data.val;
        list = ll_delete(list, i);
        list = ll_insert_int(list, i, sum); 
        sum = 0;
        nd = nd->next;
        i++;
    }
    ll_print(list);
    return list;
}

linked_list PrecSum(linked_list list){
    int i = 2, sum;
    node *nd = list.head;
    linked_list newL = ll_init();
    newL = ll_insert_int(newL, 0, *(int*)nd->data.val); 
    newL = ll_insert_int(newL, 1, *(int*)nd->next->data.val); 
    while (i < list.len)
    {   
        sum = *(int*)nd->data.val + *(int*)nd->next->data.val;
        printf("%d + %d = %d\n",*(int*)nd->data.val, *(int*)nd->next->data.val, sum );
        newL = ll_insert_int(newL, i, sum); 
        sum = 0;
        nd = nd->next;
        i++;
    }
    return newL;
}
