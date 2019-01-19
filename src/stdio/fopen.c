#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "file.h"

FILE *fopen(const char *path, const char *mode) {
	FileHandlerList *li;
	//void *data;
	//TODO: mode
	
	for(li = file_handler_list; li; li = li->next) {
		if(!strncmp(li->prefix, path, strlen(li->prefix))) {
			return (FILE *) li->handler->open(path + strlen(li->prefix), mode);
		}
	}
	
	return NULL;
}
