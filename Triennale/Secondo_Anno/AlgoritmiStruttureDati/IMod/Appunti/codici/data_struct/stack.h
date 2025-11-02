#ifndef STACK_H
#define STACK_H

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct stack{
    node *head;
    int len;
}stack;

node *alloc_node(int);
stack *init_stack();
int is_empty(stack*);
void push(stack*, int);
node *pop(stack*);
node *top(stack*);
void print_stack(stack*);
void print_node(node*);

#endif 


