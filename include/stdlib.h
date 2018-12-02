#ifndef STDLIB_H_
#define STDLIB_H_

#include <stddef.h>


void *calloc(size_t nmemb, size_t size);
void *sbrk(intptr_t increment);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

#endif
