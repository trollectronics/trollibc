#include <string.h>

char *strpbrk(const char *s, const char *accept) {
	for(;;) {
		if(!*s)
			return NULL;
		
		if(strchr(accept, *s))
			return (char *) s;
		
		s++;
	}
}
