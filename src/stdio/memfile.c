#include <stddef.h>
#include <string.h>
#include <sys/file.h>
#include "file.h"

FileHandler file_hander_memfile = {
	open = NULL,
	close = NULL,
	read = file_handler_memfile_read,
	write = file_handler_memfile_write,
};

size_t file_handler_memfile_read(const void *ptr, size_t size, File *f) {
	if(!f)
		return 0;
	
	if(!ptr) {
		f->error = 1;
		return 0;
	}
	
	memcpy(ptr, f->data, size);
	f->data += size;
	
	return size;
}

size_t file_handler_memfile_write(const void *ptr, size_t size, File *f) {
	if(!f)
		return 0;
	
	if(!ptr) {
		f->error = 1;
		return 0;
	}
	
	memcpy(f->data, ptr, size);
	f->data += size;
	
	return size;
}
