#include "memory_stats.h"
#include <stdio.h>

void print_memory_stats(void) {
    printf("Memory Stats:\n");
    printf("  Total Memory       : %10zu bytes\n", MEMORY_POOL_SIZE);
    printf("  Allocated          : %10zu bytes\n", allocated_memory);
    printf("  Free               : %10zu bytes\n", free_memory);
    printf("  Fragmentation      : %8.2f%%\n",
        (free_memory - largest_free_block) * 100.0 / MEMORY_POOL_SIZE);
    printf("  Active Allocations : %10d\n", active_allocations);
    printf("  Largest Free Block : %10zu bytes\n", largest_free_block);
}
