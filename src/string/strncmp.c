#include <stddef.h>

int strncmp(const char *s1, const char *s2, size_t n) {
	size_t i;
	if(!n)
		return 0;
	for (i = 0; i < (n - 1) && s1[i] && s2[i] && s1[i] == s2[i]; i++);
	if (s1[i] != s2[i])
		return ((signed) s1[i]) - ((signed) s2[i]);
	return 0;
}
