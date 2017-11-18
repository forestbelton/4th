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
    struct prgm *cur = NULL;

    skip_whitespace(fp);
    while (!feof(fp)) {
        struct prgm *next = malloc(sizeof *next);
        next->token = ast_token_parse(fp);
        next->next = NULL;

        if (cur != NULL) {
            cur->next = next;
        } else {
            prgm = next;
        }

        cur = next;
    }

    return prgm;
}

#define OP_CHARS "~!@#$%^&*()_+`-=,./;'\\<>?:|"

struct token ast_token_parse(FILE *fp) {
    int c = fgetc(fp);
    struct token token;

    if (isdigit(c)) {
        token = ast_token_parse_natural(fp, c);
    } else if (strchr(OP_CHARS, c) != NULL) {
        token = ast_token_parse_operator(fp, c);
    } else if (c == '"') {
        token = ast_token_parse_string(fp, c);
    } else {
        assert(0);
    }

    skip_whitespace(fp);
    return token;
}

struct token ast_token_parse_natural(FILE *fp, int c) {
    struct token out;

    out.type = TOKEN_TERM;
    out.data.term.type = TYPE_INTEGER;
    out.data.term.data.intval = 0;

    while (isdigit(c)) {
        out.data.term.data.intval *= 10;
        out.data.term.data.intval += c - '0';

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
    /*char *buf = malloc(STR_SIZE);

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
    out.data.str = buf;*/

    return out;
}

void skip_whitespace(FILE *fp) {
    int c = fgetc(fp);

    while (isspace(c)) {
        c = fgetc(fp);
    }

    ungetc(c, fp);
}
