#ifndef FOURTH_OPS_H_
#define FOURTH_OPS_H_

#include "vm.h"

#define OP_TABLE_SIZE 256

enum op_name {
    OP_UNKNOWN,
    OP_DUP,
    OP_PUSH
};

typedef void (*op)(struct vm *vm, size_t *i);
extern op ops[OP_TABLE_SIZE];

extern void dup(struct vm *vm, size_t *i);
extern void push(struct vm *vm, size_t *i);

#endif
