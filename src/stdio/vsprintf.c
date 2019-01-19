#include <stdio.h>
#include <stdarg.h>
#include "file.h"
#include "memfile.h"

int vsprintf(char *str, const char *format, va_list va) {
	int r;
	File memfile = {
		.handler = &file_handler_memfile,
		.data = str,
		.error = 0,
	};
	
	r = vfprintf((FILE *) &memfile, format, va);
	
	return r;
}
