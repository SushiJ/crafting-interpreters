#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum { OP_CONSTANT, OP_RETURN } opCode;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);

void write_chunk(Chunk *chunk, uint8_t byte, int line);

void free_chunk(Chunk *chunk);

int add_constants(Chunk *chunk, Value value);

#endif
