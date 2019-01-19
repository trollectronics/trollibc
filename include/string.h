#ifndef STRING_H_
#define STRING_H_

#include <stdint.h>
#include <stddef.h>

void *memset(void *pointer, int c, size_t n);
void *memcpy(void *dest, void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memmove(void *dest, const void *src, size_t n);

char *strcat(char *dest, const char *src);
size_t strlen(const char *c);
size_t strnlen(const char *c, size_t maxlen);
char *strncpy(char *dest, const char *src, size_t max);
char *strcpy(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *str, char chr);

char *strsep(char **stringp, const char *delim);
char *strpbrk(const char *s, const char *accept);

char *strtok_r(char *str, const char *delim, char **saveptr);
char *strtok(char *str, const char *delim);

#endif
