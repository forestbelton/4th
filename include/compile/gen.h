#ifndef FOURTH_COMPILE_GEN_H_
#define FOURTH_COMPILE_GEN_H_

#include "compile/ast.h"

#include <stdint.h>

enum gen_buf_type {
    BUF_MEMORY,
    BUF_FILE
};

struct mem_buf {
    size_t size;
    size_t capacity;
    uint8_t *data;
};

struct gen_buf {
    enum gen_buf_type type;
    union {
        struct mem_buf mem;
        FILE *fp;
    } data;
};

void gen_ast(struct gen_buf *buf, struct prgm *prgm);

#endif
