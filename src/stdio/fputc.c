#include <stdio.h>

int fputc(int c, FILE *stream) {
	char cc = c;
	//TODO: return EOF on error
	fwrite(&cc, 1, 1, stream);
	return c;
}
