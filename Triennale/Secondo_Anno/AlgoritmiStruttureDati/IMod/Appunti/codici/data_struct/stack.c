#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

node *alloc_node(int elem) {
    node *n = malloc(sizeof(node));
    if (n != NULL) {
        n->data = elem;
        n->next = NULL;
    }
    return n;
}

stack *init_stack(){
    stack *s = malloc(sizeof(stack));
    if (s != NULL) {
        s->head = NULL;
        s->len = 0;
    }
    return s;
}

void push(stack *st, int elem){
    node *nd = alloc_node(elem);
    if (st->len == 0) {
        st->head = nd;
    }else{
        nd->next = st->head;
        st->head = nd;
    }
    st->len++;
}

node *pop(stack *st){
    if (st->len == 0) {
        return NULL;
    }
    node *head = st->head;
    st->head = st->head->next;
    st->len--;
    return head;
}

node *top(stack *st){
    if (st->len == 0) {
        return NULL;
    }
    node *head = st->head;
    return head;
}

void print_stack(stack *st){
    node *nd = st->head;
    int i = 0;
    printf("len: %d\n( ", st->len);
    while (nd != NULL) {
        printf("%d ", nd->data);
        nd = nd->next;
        i++;
    }
    printf(")\n");
    
}

void print_node(node *nd){
    printf("Data: %d\n", nd->data);
}

int main(){
    stack *st = init_stack();
    for (int i = 0;i < 10; i++) {
        push(st, i);
    }

    print_stack(st);
    
    node *nd = pop(st);
    print_node(nd);

    node *nd2 = top(st);
    print_node(nd2);


    print_stack(st);
    

    return 0;
}


