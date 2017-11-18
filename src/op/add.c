#include "ops.h"
#include "vm.h"

#include <assert.h>

void add(struct vm *vm, size_t *i) {
    assert(vm->top > 1);

    struct term *b = &vm->stack[vm->top - 1];
    assert(b->type == TYPE_INTEGER);

    struct term *a = &vm->stack[vm->top - 2];
    assert(a->type == TYPE_INTEGER);

    a->data.intval += b->data.intval;
    vm->top--;
}
