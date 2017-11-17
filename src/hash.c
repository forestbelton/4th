#include "hash.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>

uint32_t hash(char *data) {
    uint32_t out = 0;

    while (*data) {
        out = 33 * out + *data;
        ++data;
    }

    return out;
}

enum insert_status hash_set(struct hash *h, char *key, void *value) {
    uint32_t index;

    if (h->size >= TABLE_SIZE - 1) {
        return INSERT_FAILED;
    }

    index = hash(key) % TABLE_SIZE;
    while (h->table[index].key != NULL && strcmp(h->table[index].key, key) != 0) {
        ++index;
    }

    /* New entry instead of update */
    if (h->table[index].key == NULL) {
        h->table[index].key = key;
        ++h->size;
    }

    h->table[index].value = value;
    return INSERT_SUCCEEDED;
}

void *hash_get(struct hash *h, char *key) {
    void *out = NULL;
    uint32_t index = hash(key) % TABLE_SIZE;

    while (h->table[index].key != NULL) {
        if (strcmp(h->table[index].key, key) == 0) {
            out = h->table[index].value;
            break;
        }
    }

    return out;
}
