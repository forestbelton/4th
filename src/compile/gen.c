#include "hash.h"
#include "ops.h"
#include "compile/gen.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 512

enum op_name gen_op(const char *op);
void gen_write(struct gen_buf *buf, void *data, size_t len);

void gen_ast(struct gen_buf *buf, struct prgm *prgm) {
    if (buf->type == BUF_MEMORY) {
        buf->data.mem.size = 0;
        buf->data.mem.capacity = MEM_SIZE;
        buf->data.mem.data = malloc(MEM_SIZE);

        assert(buf->data.mem.data != NULL);
    }

    while (prgm != NULL) {
        uint8_t op = OP_PUSH;
        struct token *token = &prgm->token;

        // Write opcode
        if (token->type == TOKEN_OPERATOR) {
            op = gen_op(token->data.op);
        }
        gen_write(buf, &op, 1);

        // Write term data (if any)
        if (token->type == TOKEN_TERM) {
            gen_write(buf, &token->data.term, sizeof token->data.term);
        }

        prgm = prgm->next;
    }
}

void gen_write(struct gen_buf *buf, void *data, size_t len) {
    switch (buf->type) {
        case BUF_MEMORY:
            while (buf->data.mem.size + len > buf->data.mem.capacity) {
                size_t newCapacity = buf->data.mem.capacity * 2;

                buf->data.mem.capacity = newCapacity;
                buf->data.mem.data = realloc(buf->data.mem.data, newCapacity);

                assert(buf->data.mem.data != NULL);
            }

            memcpy(&buf->data.mem.data[buf->data.mem.size], data, len);
            buf->data.mem.size += len;

            break;

        case BUF_FILE:
            fwrite(data, len, 1, buf->data.fp);
            break;
    }
}

static struct hash op_map;

enum op_name gen_op(const char *op) {
    // Initialize operator map (one time)
    if (op_map.size == 0) {
        hash_set(&op_map, ".", (void*)OP_DUP);
    }

    const void *vop = hash_get(&op_map, op);
    assert(vop != NULL);

    return (enum op_name)vop;
}
