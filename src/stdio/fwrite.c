#include <stdio.h>
#include <string.h>
#include "file.h"

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t i;
	ssize_t r;
	size_t count = 0;
	
	File *f = (File *) stream;
	
	if(!f)
		return 0;
	
	for(i = 0; i < nmemb; i++) {
		//TODO: handle errors
		r = f->handler->write(ptr, size, f);
		ptr += size;
		count += r;
		if(f->error)
			return count;
	}
	
	return count;
}
