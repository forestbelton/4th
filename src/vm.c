#include "ops.h"
#include "vm.h"

#include <assert.h>
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
        uint8_t op = vm->prgm[i++];
        ops[op](vm, &i);
    }
}

#define LINE_WIDTH 10

void vm_dump(struct vm *vm) {
    size_t i = 0;

    printf("======================\n");
    printf("%zu elements on stack.\n", vm->top);
    printf("======================\n");

    for (i = 0; i < vm->top; ++i) {
        if (i % LINE_WIDTH != 0) {
            putchar(' ');
        } else if (i > 0) {
            putchar('\n');
        }

        struct term t = vm->stack[vm->top - i - 1];
        switch (t.type) {
            case TYPE_INTEGER:
                printf("%d", t.data.intval);
                break;

            /* Exhaustive case check */
            default:
                assert(0);
                break;
        }
    }

    printf("\n======================\n");
}
