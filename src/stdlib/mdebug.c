#include <stdlib.h>

#define MALLOC_SPACING 32

enum {
	DEBUG_API_CMD_MALLOC,
	DEBUG_API_CMD_FREE,
	DEBUG_API_CMD_OFF,
	DEBUG_API_CMD_ON,
};

static void debug_log(const char *s) {
	char c;
	char *debug_port = (char *) ~0UL;

	while((c = *s++)) {
		*debug_port = c;
	}
}

static void debug_api_raw(uint8_t c) {
	uint8_t *debug_port = (uint8_t *) ~1UL;

	*debug_port = c;
}

static void debug_api_uint32(uint32_t a) {
	debug_api_raw(a >> 24);
	debug_api_raw(a >> 16);
	debug_api_raw(a >> 8);
	debug_api_raw(a >> 0);
}

static void debug_api(uint8_t flag, uint32_t addr, uint32_t size) {
	debug_api_raw(flag);
	debug_api_uint32(addr);
	debug_api_uint32(size);
}


static char *int_to_string(unsigned long n, char *s, int base) {
	char i;
	*s = 0;
	do {
		s--;
		i = n  % base;
		i += (i > 9 ? 'A' - 10 : '0');
		*s = i;
		n /= base;
	} while(n);
	return s;
}

void *malloc_debug(size_t size, const char *f, int l) {
	char buf[25];

	debug_api(DEBUG_API_CMD_OFF, 0, 0);
	void *p = real_malloc(size + MALLOC_SPACING);
	debug_api(DEBUG_API_CMD_ON, 0, 0);
	
	debug_api(DEBUG_API_CMD_MALLOC, (uint32_t) p, (uint32_t) size);
	debug_log("malloc in ");
	debug_log(f);
	debug_log(":");
	debug_log(int_to_string(l, buf + 24, 10));
	debug_log(" addr 0x");
	debug_log(int_to_string((unsigned long) p, buf + 24, 16));
	debug_log(" siz 0x");
	debug_log(int_to_string((unsigned long) size, buf + 24, 16));
	debug_log("\n");

	return p;
}

void *calloc_debug(size_t nmemb, size_t size, const char *f, int l) {
	char buf[25];
	void *p = real_calloc(nmemb, size);
	
	debug_log("calloc in ");
	debug_log(f);
	debug_log(":");
	debug_log(int_to_string(l, buf + 24, 10));
	debug_log(" addr 0x");
	debug_log(int_to_string((unsigned long) p, buf + 24, 16));
	debug_log(" siz 0x");
	debug_log(int_to_string((unsigned long) size*nmemb, buf + 24, 16));
	debug_log("\n");

	return p;
}

void free_debug(void *p, const char *f, int l) {
	char buf[25];
	
	debug_api(DEBUG_API_CMD_FREE, (uint32_t) p, 0);

	debug_log("free in ");
	debug_log(f);
	debug_log(":");
	debug_log(int_to_string(l, buf + 24, 10));
	debug_log(" addr 0x");
	debug_log(int_to_string((unsigned long) p, buf + 24, 16));
	debug_log("\n");

	debug_api(DEBUG_API_CMD_OFF, 0, 0);
	real_free(p);
	debug_api(DEBUG_API_CMD_ON, 0, 0);
}

