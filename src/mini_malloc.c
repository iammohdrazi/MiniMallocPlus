#include "mini_malloc.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Memory pool
size_t MEMORY_POOL_SIZE = 1024 * 1024; // 1 MB
size_t allocated_memory = 0;
size_t free_memory = 1024 * 1024;
size_t largest_free_block = 1024 * 1024;
int active_allocations = 0;

static allocation_strategy_t current_strategy = FIRST_FIT;

// Simple memory block structure
typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

static uint8_t memory_pool[1024*1024];
static Block* free_list = (Block*)memory_pool;

void set_allocation_strategy(allocation_strategy_t strategy) {
    current_strategy = strategy;
}

static Block* find_free_block(size_t size) {
    Block* curr = free_list;
    Block* best = NULL;
    switch (current_strategy) {
        case FIRST_FIT:
            while (curr) {
                if (curr->free && curr->size >= size) return curr;
                curr = curr->next;
            }
            break;
        case BEST_FIT:
            while (curr) {
                if (curr->free && curr->size >= size) {
                    if (!best || curr->size < best->size) best = curr;
                }
                curr = curr->next;
            }
            return best;
        case WORST_FIT:
            while (curr) {
                if (curr->free && curr->size >= size) {
                    if (!best || curr->size > best->size) best = curr;
                }
                curr = curr->next;
            }
            return best;
        default:
            return NULL;
    }
    return NULL;
}

void* mini_malloc_debug(size_t size, const char* file, int line) {
    Block* block = find_free_block(size);
    if (!block) return NULL;

    block->free = 0;
    allocated_memory += size;
    free_memory -= size;
    if (size > largest_free_block) largest_free_block = size;
    active_allocations++;

    log_allocation((uint8_t*)block + sizeof(Block), size, file, line);
    return (uint8_t*)block + sizeof(Block);
}

void* mini_malloc(size_t size) {
    return mini_malloc_debug(size, "N/A", 0);
}

void mini_free(void* ptr) {
    if (!ptr) return;
    Block* block = (Block*)((uint8_t*)ptr - sizeof(Block));
    block->free = 1;
    allocated_memory -= block->size;
    free_memory += block->size;
    active_allocations--;
    log_free(ptr);
}
