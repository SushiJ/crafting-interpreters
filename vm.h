#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
    Chunk *chunk;
    uint8_t *ip;
} VM;

typedef enum {
    INTEPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTEPRET_RUNTIME_ERROR
} Interpret_Result;

void init_vm();
void free_vm();

Interpret_Result interpret(Chunk *chunk);

#endif
