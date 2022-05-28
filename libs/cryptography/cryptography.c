#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cryptography.h"

char* XORCipher(char* data, char* key, size_t data_len) {
    size_t key_len = strlen(key);

    /* Allocates output string */
    char* output = (char*)malloc(sizeof(char) * data_len + 1);

    /* Encrypts data */
    int i;
    for(i = 0; i < data_len; i++) {
        output[i] = data[i] ^ key[i % key_len];
    }

    return output;
}