#include <stdint.h>

static uint32_t _rand_state = 0xDEADBEEF;

unsigned int rand(void) {
	uint32_t x = rand_state;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return _rand_state = x;
}


void srand(unsigned int seed) {
	if (!seed)
		seed = (unsigned int) 0xDEADBEEF;
	_rand_state = seed;
}
