#include <stdint.h>
#include <stddef.h>
#include <string.h>

void *memcpy(void *dest, const void *src, size_t n) {
	uint8_t *p1 = dest;
	const uint8_t *p2 = src;
	
	while(n) {
		n--;
		p1[n] = p2[n];
	}
	
	return dest;
}
