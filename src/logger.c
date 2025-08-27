#include "logger.h"
#include <stdio.h>

void log_allocation(uint8_t* ptr, size_t size, const char* file, int line) {
    FILE* fp = fopen("memory_log.txt", "a");
    if (fp) {
        fprintf(fp, "ALLOC: %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
        fclose(fp);
    }
}

void log_free(void* ptr) {
    FILE* fp = fopen("memory_log.txt", "a");
    if (fp) {
        fprintf(fp, "FREE : pointer at %p\n", ptr);
        fclose(fp);
    }
}
