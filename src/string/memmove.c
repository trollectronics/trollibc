#include <stdint.h>
#include <stddef.h>

void *memmove(void *dest, const void *src, size_t n) {
	uint8_t *p1 = dest;
	const uint8_t *p2 = src;
	if(src > dest) {
		size_t i;
		for(i = 0; i < n; i++) {
			p1[i] = p2[i];
		}
	} else {
		while(n) {
			n--;
			p1[n] = p2[n];
		}
	}
	
	return dest;
}
