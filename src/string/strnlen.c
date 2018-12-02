#include <stddef.h>

size_t strnlen(const char *c, size_t maxlen) {
	size_t i;

	for (i = 0; i < maxlen && c[i]; i++);
	return i;
}
