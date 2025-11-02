#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int data;
} node;

typedef struct linked_list {
    node *head;
    int len;
    int max;
} linked_list;

linked_list *ll_init(void) {
    linked_list *l = malloc(sizeof(linked_list));
    l->head = NULL;
    l->len = 0;
    return l;
}

void ll_in0(linked_list *list, int elem) {
    node *nd = malloc(sizeof(node));
    nd->data = elem;
    nd->next = list->head;
    list->head = nd;
    list->len++;
}

void buckerSort(linked_list list) {
    int max = a.max++;
    int *y = calloc(max, sizeof(max));

    for (int i = a.len - 1; i = > 0; i--) {
    }
}
