#include "memory_stats.h"
#include "mini_malloc.h"
#include <stdio.h>

void print_memory_stats() {
    size_t allocated = 0, free_mem = 0, largest = 0, active = 0;
    Block* curr = free_list;

    while (curr) {
        if (curr->free) {
            free_mem += curr->size;
            if (curr->size > largest) largest = curr->size;
        } else {
            allocated += curr->size;
            active++;
        }
        curr = curr->next;
    }

    double frag = allocated ? ((double)free_mem / (allocated + free_mem)) * 100.0 : 0;

    printf("Memory Stats:\n");
    printf("  Total Memory       : %10zu bytes\n", (size_t)MEMORY_POOL_SIZE);
    printf("  Allocated          : %10zu bytes\n", allocated);
    printf("  Free               : %10zu bytes\n", free_mem);
    printf("  Fragmentation      : %7.2f%%\n", frag);
    printf("  Active Allocations : %10zu\n", active);
    printf("  Largest Free Block : %10zu bytes\n", largest);
}
