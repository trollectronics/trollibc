#include <stddef.h>
#include <stdint.h>

int memcmp(const void *s1, const void *s2, size_t n) {
	const char *ss1 = s1, *ss2 = s2;
	size_t i;
	if(!n)
		return 0;
	for (i = 0; i < (n - 1) && ss1[i] == ss2[i]; i++);
	if (ss1[i] != ss2[i])
		return ((signed) ss1[i]) - ((signed) ss2[i]);
	return 0;
}
