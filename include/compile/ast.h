#ifndef FOURTH_AST_H_
#define FOURTH_AST_H_

#include <stdio.h>

enum token_type {
    TOKEN_UNKNOWN,
    TOKEN_NATURAL,
    TOKEN_STRING,
    TOKEN_OPERATOR
};

struct token {
    enum token_type type;
    union {
        int nat;
        char *str;
        char *op;
    } data;
};

struct prgm {
    struct token token;
    struct prgm *next;
};

struct prgm *ast_parse(FILE *fp);

#endif
