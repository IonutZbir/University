#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct queue {
  node *head;
  node *tail;
  int len;
} queue;

node *alloc_node(int);
queue *init_queue();
int isEmpty(queue *);
void equeue(queue *, int);
node *dequeue(queue *);
node *first(queue *);
void print_queue(queue *);
void print_node(node *);

#endif
