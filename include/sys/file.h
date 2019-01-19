#ifndef SYS_FILE_H_
#define SYS_FILE_H_

#include <stddef.h>

typedef struct FileHandler FileHandler;
struct FileHandler {
	File *(*open)(const char *path, const char *mode);
	int (*close)(File *f);
	size_t (*read)(const void *ptr, size_t size, File *f);
	size_t (*write)(const void *ptr, size_t size, File *f);
};

typedef struct File File;
struct File {
	FileHandler *handler;
	void *data;
	int error;
};

#endif
