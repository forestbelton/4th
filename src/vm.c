#include "ops.h"
#include "vm.h"

#include <stdint.h>

void vm_init(struct vm *vm, uint8_t *prgm, size_t len) {
    vm->top = 0;
    vm->prgm = prgm;
    vm->len = len;
}

void vm_exec(struct vm *vm) {
    size_t i = 0;

    while (i < vm->len) {
        uint8_t op = vm->prgm[i];
        ops[op](vm);
    }
}
