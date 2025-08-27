#include "mini_malloc.h"
#include "memory_stats.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("\n=== MiniMallocPlus ===\n\n");

    set_allocation_strategy(FIRST_FIT);

    // Step 1: Allocate memory
    void* a = mini_malloc(100);
    void* b = mini_malloc(200);
    void* c = mini_malloc(50);

    if (a) memset(a, 0, 100);
    if (b) memset(b, 1, 200);
    if (c) memset(c, 2, 50);

    printf("1) Allocate a=100, b=200, c=50\n");
    print_memory_stats();

    // Step 2: Free b
    mini_free(b);

    printf("\n2) Free b (200 bytes)\n");
    print_memory_stats();

    // Step 3: Allocate d
    void* d = mini_malloc(150);
    if (d) memset(d, 3, 150);

    printf("\n3) Allocate d=150\n");
    print_memory_stats();

    printf("\n=== End of Demo ===\n");
    return 0;
}
