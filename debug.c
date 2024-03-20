#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "value.h"

static int simple_instruction(const char *name, int offset);

static int constant_intruction(const char *name, Chunk *chunk, int offset);

void disassemble_chunk(Chunk *chunk, const char *name) {
    printf("-- %s --\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset);
    }
}

int disassemble_instruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("  | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
    case OP_CONSTANT:
        return constant_intruction("OP_CONSTANT", chunk, offset);

    case OP_RETURN:
        return simple_instruction("OP_RETURN", offset);

    default:
        printf("UNKNOWN OP_CODE %d\n", instruction);
        return offset + 1;
    }
}

static int constant_intruction(const char *name, Chunk *chunk, int offset) {

    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);

    print_value(chunk->constants.values[constant]);

    printf("'\n");

    return offset + 2;
}

static int simple_instruction(const char *name, int offset) {
    printf("%s\n", name);

    return offset + 1;
}
