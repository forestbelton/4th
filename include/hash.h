#ifndef FOURTH_HASH_H_
#define FOURTH_HASH_H_

#include <stddef.h>

#define TABLE_SIZE 512

struct hash_entry {
    char *key;
    void *value;
};

struct hash {
    size_t size;
    struct hash_entry table[TABLE_SIZE];
};

enum insert_status {
    INSERT_SUCCEEDED,
    INSERT_FAILED
};

enum insert_status hash_set(struct hash *h, char *key, void *value);

void *hash_get(struct hash *h, char *key);

#endif
