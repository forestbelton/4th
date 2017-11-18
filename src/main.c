#include "ops.h"
#include "vm.h"
#include "compile/ast.h"

#include <stdio.h>
#include <string.h>

int main() {
    struct prgm *prgm = ast_parse(stdin);

    /*struct vm vm;

    struct term one;
    one.type = TYPE_INTEGER;
    one.data.intval = 1;

    uint8_t prgm[1 + sizeof (struct term)] = { OP_PUSH };
    memcpy(&prgm[1], &one, sizeof one);

    vm_init(&vm, &prgm[0], sizeof prgm);
    vm_exec(&vm);

    vm_dump(&vm);*/

    return 0;
}
