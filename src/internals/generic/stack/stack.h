#ifndef STACK_H
#define STACK_H

#include <internals/generic/array/array.h>

#define EMPTY_STACK 0

#define Stack(type) Array(type)

#define init_stack(type) init_array(type, 1)

#define get_stack_count(stack) get_array_length(stack)

#define push_stack(stack, item) add_array(stack, item)

#define peek_stack(stack) stack[get_array_length(stack) - 1]

#define pop_stack(stack)                                                                                               \
    peek_stack(stack);                                                                                                 \
    {                                                                                                                  \
        remove_array(stack, get_array_length(stack) - 1);                                                              \
    }

#define free_stack(stack) free_array(stack)

#define clear_stack(stack) clear_array(stack)

#endif