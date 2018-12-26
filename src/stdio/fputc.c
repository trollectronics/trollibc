#include <stdio.h>

int fputc(int c, FILE *stream) {
	fwrite(&c, 1, 1, stream);
}
