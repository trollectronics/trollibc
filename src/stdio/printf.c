#include <stdio.h>
#include <stdarg.h>

int printf(const char *format, ...) {
	int ret;
	va_list va;
	va_start (va, format);
	ret = vprintf(format, va);
	va_end(va);
	return ret;
}
