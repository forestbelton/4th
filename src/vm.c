#include "ops.h"
#include "vm.h"

#include <stdint.h>
#include <stdio.h>

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

void vm_dump(struct vm *vm) {
    size_t i = 0;

    printf("======================\n");
    printf("%zu elements on stack.\n", vm->top);
    printf("======================\n");

    for (i = 0; i < vm->top; ++i) {
        if (i % 10 != 0) {
            putchar(' ');
        } else if (i > 0) {
            putchar('\n');
        }

        struct term t = vm->stack[vm->top - i];
        switch (t.type) {
            case TYPE_INTEGER:
                printf("%d", t.data.intval);
                break;
        }
    }

    printf("\n======================\n");
}
