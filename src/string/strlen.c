#include <stddef.h>
#include <string.h>

size_t strlen(const char *c) {
	size_t i = 0;

	while(*c++)
		i++;
	return i;
}
