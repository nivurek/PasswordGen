#include "algorithms.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/******************************************************************************
 * LL_push
 * Adds data to front of linked list.
******************************************************************************/
void LL_push(LinkedList_t* list, entry_t* data) {
    /* Allocating memory to new node */
    LLNode_t* node = (LLNode_t*)malloc(sizeof(LLNode_t));

    node->data = data;
    node->next = list->head;

    /* Updating head of Linked list to new node */
    list->head = node;
    (list->size)++;
}

/******************************************************************************
 * LL_pop
 * Removes data from front of linked list.
******************************************************************************/
void LL_pop(LinkedList_t* list) {
    /* Edge case where list is already empty */
    if(list->size <= 0) {
        return;
    }
    
    /* Creates a temporary reference to the node being popped */
    LLNode_t* node = list->head;

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

/******************************************************************************
 * LL_front
 * Returns data from front of linked list.
******************************************************************************/
entry_t* LL_front(LinkedList_t* list) {
    /* If the list is not empty, return the data held in the head.
       Otherwise, return NULL */
    if(list->size > 0) {
        return list->head->data;
    }
    else {
        return NULL;
    }
}

/******************************************************************************
 * LL_remove  
 * Removes node at position in linked list (indexed from 0).
******************************************************************************/
void LL_remove(LinkedList_t* list, unsigned int position) {
    /* Edge case where position is outside the list */
    if(position >= list->size) {
        return;
    }
    else if(position == 0) {
        LL_pop(list);
        return;
    }

    LLNode_t* current = list->head;

    /* Gets the node 1 before the node to delete */
    int i;
    for(i = 0; i < position - 1; i++) {
        current = current->next;
    }

    /* Removing node from list */
    LLNode_t* temp = current->next;
    current->next = current->next->next;

    /* Freeing memory & reducing list size by 1 */
    free(temp->data);
    free(temp);
    (list->size)--;

}

/******************************************************************************
 * LL_get
 * Returns pointer to data at position in linked list (indexed from 0).
******************************************************************************/
entry_t* LL_get(LinkedList_t* list, unsigned int position) {
    /* Returns NULL if position is outside of the list */
    if(position >= list->size) {
        return NULL;
    }
    
    LLNode_t* current = list->head;

    /* Finds node at position */
    int i;
    for(i = 0; i < position; i++) {
        current = current->next;
    }

    /* Returns pointer to data at position */
    return current->data;
}