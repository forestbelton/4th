#ifndef FOURTH_OPS_H_
#define FOURTH_OPS_H_

#include "vm.h"

#define OP_TABLE_SIZE 256

enum op_name {
    OP_DUP
};

typedef void (*op)(struct vm *vm);
extern op ops[OP_TABLE_SIZE];

extern void dup(struct vm *vm);

#endif
