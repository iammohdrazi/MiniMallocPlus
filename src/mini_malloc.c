#include "mini_malloc.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

uint8_t memory_pool[MEMORY_POOL_SIZE];
Block* free_list = NULL;
AllocationStrategy current_strategy = FIRST_FIT;

// Initialize free list
static void init_memory() {
    if (!free_list) {
        free_list = (Block*)memory_pool;
        free_list->size = MEMORY_POOL_SIZE - sizeof(Block);
        free_list->free = 1;
        free_list->next = NULL;
    }
}

// Find a free block depending on strategy
static Block* find_block(size_t size) {
    Block *curr = free_list;
    Block *best = NULL;
    static Block* last_alloc = NULL; // for next-fit

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

        case NEXT_FIT:
            curr = last_alloc ? last_alloc : free_list;
            Block* start = curr;
            do {
                if (curr->free && curr->size >= size) {
                    last_alloc = curr;
                    return curr;
                }
                curr = curr->next ? curr->next : free_list;
            } while (curr != start);
            break;

        case QUICK_FIT:
            // Simplified: use first fit
            while (curr) {
                if (curr->free && curr->size >= size) return curr;
                curr = curr->next;
            }
            break;
    }
    return NULL;
}

void* mini_malloc(size_t size) {
    init_memory();
    Block* block = find_block(size);
    if (!block) return NULL;

    if (block->size > size + sizeof(Block)) {
        Block* new_block = (Block*)((uint8_t*)block + sizeof(Block) + size);
        new_block->size = block->size - size - sizeof(Block);
        new_block->free = 1;
        new_block->next = block->next;
        block->next = new_block;
        block->size = size;
    }
    block->free = 0;
    log_allocation((uint8_t*)block + sizeof(Block), size, __FILE__, __LINE__);
    return (uint8_t*)block + sizeof(Block);
}

void mini_free(void* ptr) {
    if (!ptr) return;
    Block* block = (Block*)((uint8_t*)ptr - sizeof(Block));
    block->free = 1;
    log_free(ptr);

    // merge adjacent free blocks
    Block* curr = free_list;
    while (curr) {
        if (curr->free && curr->next && curr->next->free) {
            curr->size += sizeof(Block) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void set_allocation_strategy(AllocationStrategy strategy) {
    current_strategy = strategy;
}
