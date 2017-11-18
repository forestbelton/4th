#include "ops.h"
#include "vm.h"
#include "compile/ast.h"
#include "compile/gen.h"

#include <stdio.h>
#include <string.h>

int main() {
    printf("Parsing input...\n");
    struct prgm *prgm = ast_parse(stdin);

    struct gen_buf buf;
    buf.type = BUF_MEMORY;

    printf("Generating bytecode...\n");
    gen_ast(&buf, prgm);

    size_t i = 0;
    for (i = 0; i < buf.data.mem.size; ++i) {
        printf("%02x ", buf.data.mem.data[i]);
    }
    printf("\n");


    struct vm vm;
    vm_init(&vm, &buf.data.mem.data[0], buf.data.mem.size);

    printf("Executing bytecode...\n");
    vm_exec(&vm);
    vm_dump(&vm);

    return 0;
}
