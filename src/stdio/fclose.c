#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "file.h"

int fclose(FILE *stream) {
	if(!stream)
		return -1;
	
	return ((File *) stream)->handler->close((File *) stream);
}
