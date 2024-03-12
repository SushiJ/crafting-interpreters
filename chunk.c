#include "chunk.h"
#include "memory.h"
#include "value.h"

void init_chunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->line_arr->lines = NULL;
    chunk->line_arr->count = 0;
    init_value_array(&chunk->constants);
}

void write_chunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
    }

    // INFO: This should work? probably?
    if (chunk->line_arr->count < chunk->line_arr->capacity + 1) {
        int old_capacity = chunk->line_arr->capacity;

        chunk->line_arr->capacity = GROW_CAPACITY(old_capacity);

        chunk->line_arr->lines =
            GROW_ARRAY(uint8_t, chunk->line_arr->lines, old_capacity,
                       chunk->line_arr->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;

    uint8_t lcount = chunk->line_arr->count;
    uint8_t ln = get_line(chunk, lcount);

    if (ln != line) {
        chunk->line_arr->lines[lcount] = line;
        chunk->line_arr->count++;
    }
}

int get_line(Chunk *chunk, int idx) { return chunk->line_arr->lines[idx]; }

void free_chunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->line_arr->lines, chunk->line_arr->capacity);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}

int add_constants(Chunk *chunk, Value value) {
    write_value_array(&chunk->constants, value);

    // return idx where constant was written at
    return chunk->constants.count - 1;
}
