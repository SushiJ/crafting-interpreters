#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum { OP_CONSTANT, OP_RETURN } opCode;

// INFO: this is not pretty but should work? don't quote me on that
typedef struct {
    uint8_t *lines;
    int count;
    int capacity;
} LinesArray;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    LinesArray *line_arr;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);

void write_chunk(Chunk *chunk, uint8_t byte, int line);

void free_chunk(Chunk *chunk);

int add_constants(Chunk *chunk, Value value);

int get_line(Chunk *chunk, int idx);

#endif
