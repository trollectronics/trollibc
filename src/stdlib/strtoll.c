#include <ctype.h>
#include <limits.h>

long long int strtoll(const char *nptr, char **endptr, int base) {
	long long int old = 0, val = 0;
	int sign = 1, num;
	char c;

	if (base < 0 || base > 36)
		return 0; // TODO: Set errno
	while (*nptr && isspace(*nptr))
		nptr++;
	if (!*nptr)
		goto end;
	if (*nptr == '-')
		sign = -1, nptr++;
	else if (*nptr == '+')
		sign = 1, nptr++;
	if (!*nptr)
		goto end;
	
	if (!base) {
		if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
			base = 16, nptr += 2;
		else if (nptr[0] == '0')
			base = 8, nptr++;
		else
			base = 10;
	}

	for (; *nptr; nptr++) {
		c = *nptr;
		if (c >= '0' && c <= '9')
			num = c - '0';
		else {
			c &= ~(0x20);
			if (c < 'A' || c > 'Z')
				goto end;
			num = c - 'A' + 10;
		}

		if (num >= base)
			goto end;
		val *= base;
		val += num;
		if (val < old)
			goto overflow;
		old = val;
	}

	val *= sign;
	goto end;

overflow:
	/* TODO: Set errno */
	val = (sign < 0) ? LLONG_MIN : LLONG_MAX;
		
end:
	if (endptr)
		*endptr = (char *) nptr;
	return val;
}
