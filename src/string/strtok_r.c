#include <string.h>

char *strtok_r(char *str, const char *delim, char **saveptr) {
	char *tok;
	
	if(str) {
		/* First call */
		*saveptr = str;
	}
	
	tok = *saveptr;
	
	if(!tok)
		return NULL;
	
	*saveptr = strpbrk(*saveptr, delim);
	while(*saveptr && **saveptr) {
		**saveptr = 0;
		(*saveptr)++;
		
		if(!**saveptr) {
			*saveptr = NULL;
			break;
		}
		
		if(!strchr(delim, **saveptr))
			break;
	}
	
	return tok;
}
