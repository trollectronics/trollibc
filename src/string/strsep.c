#include <string.h>

char *strsep(char **stringp, const char *delim) {
	char *tok;
	
	if(!stringp || !*stringp)
		return NULL;
	
	tok = *stringp;
	*stringp = strpbrk(tok, delim);
	if(*stringp) {
		**stringp = 0;
		(*stringp)++;
	}
	
	return tok;
}
