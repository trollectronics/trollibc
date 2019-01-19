#include <stddef.h>
#include <string.h>

char *strrchr(const char *str, char chr) {
	const char *end;
	end = str + strlen(str) - 1;
	
	for (; end >= str; end--)
		if (*end == chr)
			return (char *) end;
	return (char *) NULL;
}