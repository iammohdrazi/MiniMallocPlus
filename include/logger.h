#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>

void log_allocation(void* ptr, size_t size, const char* file, int line);
void log_free(void* ptr);

#endif // LOGGER_H
