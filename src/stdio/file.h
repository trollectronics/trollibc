#ifndef FILE_H_
#define FILE_H_

#include <sys/file.h>

typedef struct FileHandlerList FileHandlerList;
struct FileHandlerList {
	const char *prefix;
	FileHandler *handler;
	FileHandlerList *next;
};

extern FileHandlerList *file_handler_list;


#endif
