#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/file.h>
#include "file.h"

#pragma weak stdin
#pragma weak stdout
#pragma weak stderr

FILE *stdin = NULL;
FILE *stdout = NULL;
FILE *stderr = NULL;

FileHandlerList *file_handler_list = NULL;

int file_register_handler(const char *prefix, FileHandler *handler) {
	FileHandlerList *li = NULL;
	
	if(!prefix || !handler)
		return -1;
	
	if(!(li = malloc(sizeof(FileHandlerList))))
		return -1;
	
	li->handler = handler;
	li->prefix = prefix;
	li->next = file_handler_list;
	file_handler_list = li;
	
	return 0;
}

