#ifndef FILE_H_
#define FILE_H_

typedef enum FileType FileType;
enum FileType {
	FILE_TYPE_POSIX,
	FILE_TYPE_MEM,
};

typedef struct File File;
struct File {
	FileType type;
	int fd;
	void *data;
	int error;
};

#endif
