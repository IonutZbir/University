#include "../../functions/linked_list.h"
#include <stdio.h>
#include <string.h>

linked_list insert_from_terminal(linked_list, int, char **);
void incrementa_int(int *);

void main(int dim, char *args[])
{
    int x, n, d;
    char s[256] = "(12, 342)";
    // incrementa_int(&x);
    //&x, tira fuori l indirizzo di memoria della variabile x
    //  scanf aquisisce da terminale
    // d = scanf("(%d, %d)", &x, &n);
    //  l output di scanf è il numero di conversioni riuscite
    // printf("%d, %d, %d\n", x, n, d);

    // sscanf acquisce da un stringa memorizzata nel programma
    // d = sscanf(s, "(%d, %d)", &x, &n);

    linked_list list = init();
    list = insert_from_terminal(list, dim, args);
    printf("%d\n", list.len);
    print_llist(list);
    //list = insert(list, list.len - 1, 4.54);
}

void incrementa_int(int *x) { (*x)++; }

linked_list insert_from_terminal(linked_list list, int dim, char **args)
{ // O(n) non O(n^2)
    linked_list p = init();
    float val;
    int conversion;
    node *last;
    for (int i = dim - 1; i > 0; i--)
    {
        conversion = sscanf(args[i], "%f", &val);
        if (conversion == 1)
        {
            if (list.pointer == NULL)
            {
                list = insert(list, 0, val);
            }
            else
            {
                p = insert(p, 0, val);
            }
        }
    }
    last = search(list, list.len - 1);
    last->next = p.pointer;
    list.len += p.len;
    return list;
}