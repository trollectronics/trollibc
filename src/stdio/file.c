#include <stdio.h>
#include <stddef.h>

#pragma weak stdin
#pragma weak stdout
#pragma weak stderr

FILE *stdin = NULL;
FILE *stdout = NULL;
FILE *stderr = NULL;


int file_register_handler(const char *prefix, FileHandler *handler) {
	
	return 0;
}

