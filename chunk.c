#include "chunk.h"
#include "memory.h"
#include "value.h"

void init_line_array(Lines_array *lines) {
    lines->line = NULL;
    lines->capacity = 0;
    lines->count = 0;
}

void init_chunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    init_line_array(chunk->lines);
    init_value_array(&chunk->constants);
}

void write_chunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;

    Lines_array *lines = chunk->lines;

    if (lines->count && lines->line[lines->count - 1].line == line)
        return;

    if (lines->count < lines->capacity + 1) {
        int old_capacity = lines->capacity;

        lines->capacity = GROW_CAPACITY(old_capacity);

        lines->line =
            GROW_ARRAY(Line, lines->line, old_capacity, lines->capacity);
    }

    lines->line[lines->count].line = line;
    lines->line[lines->count].offset = chunk->count - 1;
    lines->count++;
}

void free_chunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines->line, chunk->lines->capacity);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}

int add_constants(Chunk *chunk, Value value) {
    write_value_array(&chunk->constants, value);

    // return idx where constant was written at
    return chunk->constants.count - 1;
}
