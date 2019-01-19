#ifndef MEMFILE_H_
#define MEMFILE_H_

#include <stddef.h>
#include <sys/file.h>

extern FileHandler file_hander_memfile;

size_t file_handler_memfile_read(const void *ptr, size_t size, File *f);
size_t file_handler_memfile_write(const void *ptr, size_t size, File *f);

#endif
