#ifndef ALGORITHMS_H 
#define ALGORITHMS_H

struct entry {
    char url[100];
    char username [50];
    char password[50];
};
typedef struct entry entry_t;

/******************************************************************************
 * Min Heap
******************************************************************************/
struct MinHNode {
    char data;
    unsigned freq;
    struct MinHNode *left, *right;
};
typedef struct MinHNode MHNode;

struct MinHeap {
    unsigned size;
    unsigned capacity;
    MHNode **root;
};
typedef struct MinHeap MinHeap;

MinHeap *createMinH(unsigned capacity);


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
 * Removes data at position in linked list (indexed from 0).
******************************************************************************/
void LL_remove(LinkedList* list, unsigned int position);
/******************************************************************************
 * Get
 * Returns data at position in linked list (indexed from 0).
******************************************************************************/
void LL_get(LinkedList* list, unsigned int position);

#endif