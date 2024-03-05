#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_capacity, new_capacity)                  \
    (type *)reallocate(pointer, sizeof(type) * (new_capacity),                 \
                       sizeof(type) * (new_capacity))

void *reallocate(void *ptr, size_t old_size, size_t new_size);

#endif
