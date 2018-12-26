#include <stdio.h>
#include "file.h"

int vsprintf(char *str, const char *format, va_list va) {
	int r;
	File memfile = {
		.type = FILE_TYPE_MEM,
		.data = str,
		.error = 0,
	};
	
	r = vfprintf((FILE *) &memfile, format, va);
	
	return r;
}
