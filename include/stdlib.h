#ifndef STDLIB_H_
#define STDLIB_H_

#include <stddef.h>
#include <stdint.h>

typedef int64_t ssize_t;
typedef int64_t off_t;

void *calloc(size_t nmemb, size_t size);
void *sbrk(intptr_t increment);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

long long int strtoll(const char *nptr, char **endptr, int base);

#endif
