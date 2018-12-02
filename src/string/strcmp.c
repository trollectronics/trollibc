#include <stddef.h>
#include <string.h>

int strcmp(const char *s1, const char *s2) {
	int i;
	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
	if (s1[i] != s2[i])
		return ((signed) s1[i]) - ((signed) s2[i]);
	return 0;
}
