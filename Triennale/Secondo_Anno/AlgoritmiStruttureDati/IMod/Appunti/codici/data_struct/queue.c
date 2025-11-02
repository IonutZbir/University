#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

node *alloc_node(int elem) {
    node *n = malloc(sizeof(node));
    if (n != NULL) {
        n->data = elem;
        n->next = NULL;
    }
    return n;
}

queue *init_queue() {
    queue *q = malloc(sizeof(queue));
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->len = 0;
    }
    return q;
}

int isEmpty(queue *q) {
    if (q->len == 0)
        return 1;
    return 0;
}

void enqueue(queue *q, int elem) {
    node *nd = alloc_node(elem);
    if (isEmpty(q)) {
        q->head = nd;
        q->tail = nd;
    } else {
        q->tail->next = nd;
        q->tail = nd;
    }

    q->len++;
}

node *dequeue(queue *q) {
    if (!isEmpty(q)) {
        node *nd = q->head;
        q->head = q->head->next;
        q->len--;
        return nd;
    }
    return NULL;
}

node *first(queue *q) {
    if (!isEmpty(q)) {
        node *nd = q->head;
        return nd;
    }
    return NULL;
}

void print_queue(queue *q) {
    node *nd = q->head;
    int i = 0;
    printf("len: %d\n( ", q->len);
    while (i < q->len) {
        printf("%d ", nd->data);
        nd = nd->next;
        i++;
    }
    printf(")\n");
}

void print_node(node *nd) { printf("Data: %d\n", nd->data); }

int main() {
    queue *q = init_queue();
    for (int i = 0; i < 10; i++) {
        enqueue(q, i);
    }

    print_queue(q);

    node *nd = dequeue(q);
    print_node(nd);

    node *nd2 = first(q);
    print_node(nd2);

    print_queue(q);

    return 0;
}
