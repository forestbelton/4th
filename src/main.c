#include "vm.h"
#include <stdio.h>

int main() {
    struct vm vm;

    vm_init(&vm, NULL, 0);
    vm_exec(&vm);

    vm_dump(&vm);

    return 0;
}
