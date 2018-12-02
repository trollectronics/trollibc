#include <stddef.h>
#include <string.h>

char *strncpy(char *dest, const char *src, size_t max) {
	size_t i;

	for (i = 0; i < max && src[i]; i++)
		dest[i] = src[i];
	if (i == max)
		dest[i - 1] = 0;
	else
		dest[i] = 0;
	return dest;
}
