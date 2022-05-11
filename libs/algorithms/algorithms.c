#include "algorithms.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

MinHeap *createMinH(unsigned capacity) {

}
void LL_push(LinkedList* list, entry_t* data) {
    /* Allocating memory to new node */
    LLNode* node = (LLNode*)malloc(sizeof(LLNode));

    node->data = data;
    node->next = list->head;

    /* Updating head of Linked list to new node */
    list->head = node;
    (list->size)++;
}

void LL_pop(LinkedList* list) {
    if(list->size <= 0) {
        return;
    }
    
    LLNode* node = list->head;
    if(list->size > 1) {
        list->head = node->next;
    }
    else {
        list->head = NULL;
    }

    (list->size)--;
    free(node);
}

entry_t* LL_front(LinkedList* list) {
    if(list->size > 0) {
        return list->head->data;
    }
    else {
        return NULL;
    }
}