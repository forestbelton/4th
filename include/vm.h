#ifndef FOURTH_VM_H_
#define FOURTH_VM_H_

#include <stddef.h>
#include <stdint.h>

#define STACK_SIZE 512

enum term_type {
    TYPE_INTEGER
};

struct term {
    enum term_type type;
    union {
        int intval;
    } data;
};

struct vm {
    uint8_t *prgm;
    size_t len;
    size_t top;
    struct term stack[STACK_SIZE];
};

void vm_init(struct vm *vm, uint8_t *prgm, size_t len);

void vm_exec(struct vm *vm);

#endif
