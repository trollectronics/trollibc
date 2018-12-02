#include <stddef.h>
#include <string.h>

char *strchr(const char *str, char chr) {
	for (; *str; str++)
		if (*str == chr)
			return (char *) str;
	return (char *) NULL;
}
