#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum { OP_CONSTANT, OP_RETURN } opCode;

// INFO: this is not pretty but should work? don't quote me on that
typedef struct {
    int line;
    int offset;
} Line;

typedef struct {
    Line *line;
    int count;
    int capacity;
} Lines_array;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    Lines_array *lines;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);

void init_line_array(Lines_array *lines);

void write_chunk(Chunk *chunk, uint8_t byte, int line);

void free_chunk(Chunk *chunk);

int add_constants(Chunk *chunk, Value value);

int get_line(Lines_array *lines, int idx);

#endif
