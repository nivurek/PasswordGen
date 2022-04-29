#ifndef ALGORITHMS_H 
#define ALGORITHMS_H

struct MinHNode {
    char data;
    unsigned freq;
    struct MinHNode *left, *right;
};
typedef struct MinHNode MinHNode_t;

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHNode_t **root;
};
typedef struct MinHeap MinHeap_t;

MinHeap_t *createMinH(unsigned capacity);

#endif