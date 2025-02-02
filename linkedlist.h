#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    int y;
    struct Node* next;
    struct Node * prev;
} Node;

Node* createNode(int x, int y);

void destroyNode(Node* node);

void destroyList(Node* head);
#endif