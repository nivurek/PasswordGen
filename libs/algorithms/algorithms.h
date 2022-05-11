#ifndef ALGORITHMS_H 
#define ALGORITHMS_H

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
    void* data;
    struct LLNode* next;
};
typedef struct LLNode LLNode;

struct LinkedList {
    unsigned int size;
    LLNode* head;
};
typedef struct LinkedList LinkedList;

void LL_push(LinkedList* list, void* data, size_t data_size);
void LL_pop(LinkedList* list);
void* LL_front(LinkedList* list);
void LL_remove(LinkedList* list, unsigned int position);
void LL_find(LinkedList* list, void* data);

#endif