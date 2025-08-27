#include <stdio.h>
#include <stdlib.h>
#include "mini_malloc.h"
#include "memory_stats.h"

// Function to run the demo allocations
void run_demo() {
    printf("Demo Allocations:\n");

    // Sample allocations
    void* a = mini_malloc(100);
    void* b = mini_malloc(200);
    void* c = mini_malloc(50);

    // Silence unused variable warnings
    (void)a;
    (void)c;

    // Print memory stats
    print_memory_stats();

    // Free one block
    printf("\nFree b (200 bytes)\n");
    mini_free(b);
    print_memory_stats();

    // Allocate another block
    void* d = mini_malloc(150);
    (void)d; // Silence unused variable warning
    printf("\nAllocate d=150 bytes\n");
    print_memory_stats();
}

int main() {
    int choice;
    char cont = 'y';

    while(cont == 'y' || cont == 'Y') {
        printf("\n=== MiniMallocPlus ===\n\n");
        printf("Select allocation strategy:\n");
        printf("1) First-Fit\n");
        printf("2) Best-Fit\n");
        printf("3) Worst-Fit\n");
        printf("4) Next-Fit\n");
        printf("5) Quick-Fit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: set_allocation_strategy(FIRST_FIT); break;
            case 2: set_allocation_strategy(BEST_FIT); break;
            case 3: set_allocation_strategy(WORST_FIT); break;
            case 4: set_allocation_strategy(NEXT_FIT); break;
            case 5: set_allocation_strategy(QUICK_FIT); break;
            default:
                printf("Invalid choice. Using First-Fit by default.\n");
                set_allocation_strategy(FIRST_FIT);
                choice = 1;
        }

        // Strategy names
        const char* strategy_names[] = {"FIRST-FIT", "BEST-FIT", "WORST-FIT", "NEXT-FIT", "QUICK-FIT"};
        printf("\n=== %s ===\n\n", strategy_names[choice-1]);

        run_demo();

        printf("\nContinue? (y/n): ");
        scanf(" %c", &cont);
    }

    printf("\n=== End of MiniMallocPlus Demo ===\n");
    return 0;
}
