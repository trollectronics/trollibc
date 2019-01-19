#ifndef STDIO_H_
#define STDIO_H_

#include <stddef.h>
#include <stdarg.h>

typedef void FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);

int vfprintf(FILE *stream, const char *format, va_list va);
int vprintf(const char *format, va_list va);
int printf(const char *format, ...);
int vsprintf(char *str, const char *format, va_list va);
int sprintf(char *str, const char *format, ...);

#endif
