#include <stdio.h>
#include <stdarg.h>

int vprintf(const char *format, va_list va) {
	return vfprintf(stdout, format, va);
}
