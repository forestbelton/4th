#include "ops.h"

op ops[OP_TABLE_SIZE] = {
    [OP_DUP] = dup,
    [OP_PUSH] = push,
    [OP_ADD] = add
};
