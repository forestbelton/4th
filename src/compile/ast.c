#include "compile/ast.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct token ast_token_parse(FILE *fp);
struct token ast_token_parse_natural(FILE *fp, int c);
struct token ast_token_parse_operator(FILE *fp, int c);
struct token ast_token_parse_string(FILE *fp, int c);
void skip_whitespace(FILE *fp);

struct prgm *ast_parse(FILE *fp) {
    struct prgm *prgm = NULL;

    skip_whitespace(fp);
    while (!feof(fp)) {
        struct prgm *next = malloc(sizeof *next);
        next->token = ast_token_parse(fp);
        next->next = NULL;

        if (prgm != NULL) {
            prgm->next = next;
        }

        prgm = next;
    }

    return prgm;
}

#define OP_CHARS "~!@#$%^&*()_+`-=,./;'\\<>?:|"

struct token ast_token_parse(FILE *fp) {
    int c = fgetc(fp);
    enum token_type type = TOKEN_UNKNOWN;
    struct token token;

    if (isdigit(c)) {
        type = TOKEN_NATURAL;
    } else if (strchr(OP_CHARS, c) != NULL) {
        type = TOKEN_OPERATOR;
    } else if (c == '"') {
        type = TOKEN_STRING;
    }

    assert(type != TOKEN_UNKNOWN);
    switch (type) {
        case TOKEN_NATURAL:
            token = ast_token_parse_natural(fp, c);
            break;

        case TOKEN_OPERATOR:
            token = ast_token_parse_operator(fp, c);
            break;

        case TOKEN_STRING:
            token = ast_token_parse_string(fp, c);
            break;

        default:
            assert(0);
            break;
    }

    skip_whitespace(fp);
    return token;
}

struct token ast_token_parse_natural(FILE *fp, int c) {
    struct token out;

    out.type = TOKEN_NATURAL;
    out.data.nat = 0;

    while (isdigit(c)) {
        out.data.nat *= 10;
        out.data.nat += c - '0';

        c = fgetc(fp);
    }

    ungetc(c, fp);
    return out;
}

/* Default length of an operator, plus null byte */
#define OP_SIZE (6 + 1)

struct token ast_token_parse_operator(FILE *fp, int c) {
    size_t i = 0;
    struct token out;
    char *buf = malloc(OP_SIZE);

    assert(buf != NULL);
    do {
        // TODO: Support arbirary width operators (or not?)
        assert(i < OP_SIZE - 1);

        buf[i++] = c;
        c = fgetc(fp);
    } while(strchr(OP_CHARS, c) != NULL);

    ungetc(c, fp);
    buf[i] = 0;

    out.type = TOKEN_OPERATOR;
    out.data.op = buf;

    return out;
}

// Default length of string, plus null byte
#define STR_SIZE (20 + 1)

struct token ast_token_parse_string(FILE *fp, int c) {
    size_t i = 0;
    struct token out;
    char *buf = malloc(STR_SIZE);

    assert(buf != NULL);
    do {
        // TODO: Support arbitrary width strings
        assert(i < STR_SIZE - 1);

        // TODO: Support escaped characters
        buf[i] = c;
        c = fgetc(fp);
    } while(c != '"');

    // No ungetc here because we want to discard trailing quote
    buf[i] = 0;
    out.type = TOKEN_STRING;
    out.data.str = buf;

    return out;
}

void skip_whitespace(FILE *fp) {
    int c = fgetc(fp);

    while (isspace(c)) {
        c = fgetc(fp);
    }

    ungetc(c, fp);
}
