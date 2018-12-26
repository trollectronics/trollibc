#include <stdio.h>

int vprintf(const char *format, va_list va) {
	return vfprintf(stdout, format, va);
}
