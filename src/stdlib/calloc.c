#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mem.h>

void *calloc(size_t nmemb, size_t size) {
	void *ret;
	if((ret = malloc(nmemb*size)))
		memset(ret, 0, nmemb*size);
	
	return ret;
}
