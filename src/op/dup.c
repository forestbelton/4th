#include "ops.h"
#include "vm.h"

#include <assert.h>

void dup(struct vm *vm, size_t *i) {
    assert(vm->top > 0);

    vm->stack[vm->top] = vm->stack[vm->top - 1];
    vm->top++;
}
