#include "logger.h"
#include <stdio.h>

void log_allocation(void* ptr, size_t size, const char* file, int line) {
    FILE* f = fopen("memory_log.txt", "a");
    if (!f) return;
    fprintf(f, "ALLOC %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    fclose(f);
}

void log_free(void* ptr) {
    FILE* f = fopen("memory_log.txt", "a");
    if (!f) return;
    fprintf(f, "FREE %p\n", ptr);
    fclose(f);
}
