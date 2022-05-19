#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cryptography.h"

char* XORCipher(char* data, char* key) {
    size_t data_length = strlen(data);
    size_t key_length = strlen(key);

    /* Allocates output string */
    char* output = (char*)malloc(sizeof(char) * data_length + 1);

    /* Encrypts data */
    int i;
    for(i = 0; i < data_length; i++) {
        output[i] = data[i] ^ key[i % key_length];
    }

    output[data_length] = '\0';

    return output;
}