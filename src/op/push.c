#include "ops.h"
#include "vm.h"

#include <assert.h>

void push(struct vm *vm, size_t *i) {
    assert(vm->top + 1 < STACK_SIZE);
    assert(*i + TERM_SIZE <= vm->len);

    vm->stack[vm->top] = *(struct term *)(vm->prgm + *i);
    *i += TERM_SIZE;
    ++vm->top;
}
