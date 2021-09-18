#ifndef STDLIB_H_
#define STDLIB_H_

#include <stddef.h>
#include <stdint.h>

typedef int64_t off_t;

void *real_calloc(size_t nmemb, size_t size);
void *real_malloc(size_t size);
void *realloc(void *ptr, size_t size);
void real_free(void *ptr);

unsigned int rand(void);
void srand(unsigned int seed);


long long int strtoll(const char *nptr, char **endptr, int base);

void *malloc_debug(size_t size, const char *f, int l);
void *calloc_debug(size_t nmemb, size_t size, const char *f, int l);
void free_debug(void *p, const char *f, int l);

#ifdef DEBUG_MALLOC
#define malloc(siz) (malloc_debug((siz), __FILE__, __LINE__))
#define calloc(nmemb, siz) (calloc_debug((nmemb), (siz), __FILE__, __LINE__))
#define free(p) (free_debug((p), __FILE__, __LINE__))
#else
#define malloc(siz) (real_malloc((siz)))
#define calloc(nmemb, siz) (real_calloc((nmemb), (siz)))
#define free(p) (real_free((p)))
#endif
#endif
