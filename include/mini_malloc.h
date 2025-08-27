#ifndef MINI_MALLOC_H
#define MINI_MALLOC_H

#include <stddef.h>
#include <stdint.h>

// Memory pool size
#define MEMORY_POOL_SIZE (1024 * 1024)  // 1 MB

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT,
    NEXT_FIT,
    QUICK_FIT
} AllocationStrategy;

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

// Global memory pool
extern uint8_t memory_pool[MEMORY_POOL_SIZE];
extern AllocationStrategy current_strategy;
extern Block* free_list;

// API
void* mini_malloc(size_t size);
void mini_free(void* ptr);
void set_allocation_strategy(AllocationStrategy strategy);

#endif // MINI_MALLOC_H
