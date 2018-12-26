#ifndef STDIO_H_
#define STDIO_H_

#include <stddef.h>

typedef void FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);

int vfprintf(FILE *stream, char *format, va_list va);
int vprintf(char *format, va_list va);
int printf(char *format, ...);

#endif
