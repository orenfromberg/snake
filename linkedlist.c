#include "linkedlist.h"

Node* createNode(int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->x = x;
    node->y = y;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void destroyNode(Node* node) {
    free(node);
}

void destroyList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        destroyNode(current);
        current = next;
    }
}