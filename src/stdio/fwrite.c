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
		switch(f->type) {
			case FILE_TYPE_POSIX:
				if((r = write(f->fd, ptr, size)) < 0) {
					f->error = 1;
					return count;
				}
				break;
			
			case FILE_TYPE_MEM:
				memcpy(f->data, ptr, size);
				r = size;
				f->data += size;
				break;
		}
		ptr += size;
		count += r;
	}
	
	return count;
}
