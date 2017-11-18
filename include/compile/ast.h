#ifndef FOURTH_COMPILE_AST_H_
#define FOURTH_COMPILE_AST_H_

#include "vm.h"

#include <stdio.h>

enum token_type {
    TOKEN_UNKNOWN,
    TOKEN_TERM,
    TOKEN_OPERATOR
};

struct token {
    enum token_type type;
    union {
        struct term term;
        char *op;
    } data;
};

struct prgm {
    struct token token;
    struct prgm *next;
};

struct prgm *ast_parse(FILE *fp);

#endif
