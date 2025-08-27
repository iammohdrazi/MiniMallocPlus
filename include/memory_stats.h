#ifndef MEMORY_STATS_H
#define MEMORY_STATS_H

#include <stddef.h>

void print_memory_stats(void);

extern size_t MEMORY_POOL_SIZE;
extern size_t allocated_memory;
extern size_t free_memory;
extern size_t largest_free_block;
extern int active_allocations;

#endif // MEMORY_STATS_H
