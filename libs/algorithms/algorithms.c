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
    /* Edge case where list is already empty */
    if(list->size <= 0) {
        return;
    }
    
    /* Creates a temporary reference to the node being popped */
    LLNode* node = list->head;

    /* Updates head pointer to point to the next node in 
       the list if it exists, otherwise pointing to NULL */ 
    if(list->size > 1) {
        list->head = node->next;
    }
    else {
        list->head = NULL;
    }

    /* Freeing the memory allocated by the node & reducing size by 1 */
    (list->size)--;
    free(node->data);
    free(node);
}

entry_t* LL_front(LinkedList* list) {
    /* If the list is not empty, return the data held in the head.
       Otherwise, return NULL */
    if(list->size > 0) {
        return list->head->data;
    }
    else {
        return NULL;
    }
}

entry_t* LL_get(LinkedList* list, unsigned int position) {
    if(position >= list->size) {
        return NULL;
    }

    LLNode* current = list->head;

    int i;
    for(i = 0; i < position; i++) {
        current = current->next;
    }

    return current->data;
}