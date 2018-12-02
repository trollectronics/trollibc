#include <stdint.h>
#include <stddef.h>
#include <string.h>

void *memset(void *pointer, int c, size_t n) {
	uint8_t *p1 = pointer;
	while(n) {
		p1[--n] = c;
	}
	return pointer;
}
