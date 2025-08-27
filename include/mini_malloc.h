#ifndef MINI_MALLOC_H
#define MINI_MALLOC_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT,
    NEXT_FIT,
    QUICK_FIT
} allocation_strategy_t;

void set_allocation_strategy(allocation_strategy_t strategy);
void* mini_malloc(size_t size);
void mini_free(void* ptr);
void* mini_malloc_debug(size_t size, const char* file, int line);

#define MINI_MALLOC(size) mini_malloc_debug(size, __FILE__, __LINE__)

#endif // MINI_MALLOC_H
