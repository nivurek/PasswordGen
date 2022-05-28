#ifndef ALGORITHMS_H 
#define ALGORITHMS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct entry {
    char* url;
    char* username;
    char* password;

    size_t url_len;
    size_t user_len;
    size_t pass_len;
};
typedef struct entry entry_t;

/******************************************************************************
 * Linked List
******************************************************************************/
struct LLNode {
    entry_t* data;
    struct LLNode* next;
};
typedef struct LLNode LLNode;

struct LinkedList {
    unsigned int size;
    LLNode* head;
};
typedef struct LinkedList LinkedList;

/******************************************************************************
 * Push
 * Adds data to front of linked list.
******************************************************************************/
void LL_push(LinkedList* list, entry_t* data);
/******************************************************************************
 * Pop
 * Removes data from front of linked list.
******************************************************************************/
void LL_pop(LinkedList* list); 
/******************************************************************************
 * Front
 * Returns data from front of linked list.
******************************************************************************/
entry_t* LL_front(LinkedList* list);
/******************************************************************************
 * Remove  
 * Removes node at position in linked list (indexed from 0).
******************************************************************************/
void LL_remove(LinkedList* list, unsigned int position);
/******************************************************************************
 * Get
 * Returns pointer to data at position in linked list (indexed from 0).
******************************************************************************/
entry_t* LL_get(LinkedList* list, unsigned int position);

#endif