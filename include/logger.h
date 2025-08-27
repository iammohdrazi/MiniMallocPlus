#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>
#include <stdint.h>

void log_allocation(uint8_t* ptr, size_t size, const char* file, int line);
void log_free(void* ptr);

#endif // LOGGER_H
