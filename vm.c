#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

VM vm;

void init_vm() {}
void free_vm() {}
static Interpret_Result run();

Interpret_Result interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;

    return run();
};

static Interpret_Result run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {

#ifdef DEBUG_TRACE_EXECUTION
        disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
        case OP_RETURN: {
            return INTEPRET_OK;
        }
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            print_value(constant);
            printf("\n");
            break;
        }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}
