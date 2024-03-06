#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_capacity, new_capacity)                  \
    (type *)reallocate(pointer, sizeof(type) * (old_capacity),                 \
                       sizeof(type) * (new_capacity))

#define FREE_ARRAY(type, pointer, capacity)                                    \
    reallocate(pointer, sizeof(type) * capacity, 0);

void *reallocate(void *ptr, size_t old_size, size_t new_size);

#endif
