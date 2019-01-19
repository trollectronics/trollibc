#include <stdio.h>
#include <stdarg.h>


#define MIN(a, b) ((a) < (b) ? (a) : (b))

static char *int_to_string(unsigned long long int n, char *s, int base) {
	char i;
	do {
		s--;
		i = n  % base;
		i += (i > 9 ? 'A' - 10 : '0');
		*s = i;
		n /= base;
	} while(n);
	return s;
}

int vfprintf(FILE *f, const char *format, va_list va) {
	unsigned char pad, c;
	int i;
	unsigned int j;
	unsigned long long int num = 0;
	signed long long int signum = 0;
	
	enum {
		LENGTH_CHAR,
		LENGTH_SHORT,
		LENGTH_INT,
		LENGTH_LONG,
		LENGTH_LONG_LONG,
		LENGTH_INTMAX_T,
		LENGTH_SIZE_T,
		LENGTH_PTRDIFF_T,
	} length;
	int width;
	char prefix, base, *s;
	char buf[25];
	buf[24] = 0;
	
	for(i=0; (c = *format++);) {
		if(c != '%') {
			fputc(c, f);
			i++;
			continue;
		}
		length = LENGTH_INT;
		width = 0;
		prefix = 0;
		pad = ' ';
		base = 10;
		
		while(1) {
			switch(c = *format++) {
				case 0:
					goto end;
				case '%':
					fputc(c, f);
					i++;
					goto next;
				case '#':
					prefix = 1;
					break;
				case '0':
					if(!width) {
						pad = '0';
						break;
					}
				case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9':
					width = width*10 + (c - '0');
					break;
				case 'h':
					length = length == LENGTH_SHORT ? LENGTH_CHAR : LENGTH_SHORT;
					break;
				case 'l':
					length = length == LENGTH_LONG ? LENGTH_LONG_LONG : LENGTH_LONG;
					break;
				case 'j':
					length = LENGTH_INTMAX_T;
					break;
				case 'z':
					length = LENGTH_SIZE_T;
					break;
				case 't':
					length = LENGTH_PTRDIFF_T;
					break;
				case 'o':
					base = 8;
					if(prefix) {
						fputc('0', f);
						i++;
					}
					goto baseconv;
				case 'p':
					length = sizeof(void *);
					prefix = 1;
				case 'x':
				case 'X':
					base = 16;
					if(prefix) {
						fputs("0x", f);
						i += 2;
					}
				case 'u':
					baseconv:
					switch(length) {
						case LENGTH_CHAR:
							num = (unsigned char) va_arg(va, unsigned int);
							break;
						case LENGTH_SHORT:
							num = (unsigned short) va_arg(va, unsigned int);
							break;
						case LENGTH_INT:
							num = (unsigned int) va_arg(va, unsigned int);
							break;
						case LENGTH_LONG:
							num = (unsigned long) va_arg(va, unsigned long);
							break;
						case LENGTH_LONG_LONG:
							num = (unsigned long long) va_arg(va, unsigned long long);
							break;
						default:
							break;
					}
					goto print_num;
				case 'd':
				case 'i':
					switch(length) {
						case LENGTH_CHAR:
							signum = (signed char) va_arg(va, signed int);
							break;
						case LENGTH_SHORT:
							signum = (signed short) va_arg(va, signed int);
							break;
						case LENGTH_INT:
							signum = (signed int) va_arg(va, signed int);
							break;
						case LENGTH_LONG:
							signum = (signed long) va_arg(va, signed long);
							break;
						case LENGTH_LONG_LONG:
							signum = (signed long long) va_arg(va, signed long long);
							break;
						default:
							break;
					}
					if(signum < 0) {
						fputc('-', f);
						i++;
						num = -signum;
					} else
						num = signum;
					goto print_num;
				case 's':
					i += fputs(va_arg(va, char *), f);
					goto next;
				case 'c':
					i += fputc((char) va_arg(va, int), f);
					goto next;
			}
		}
		print_num:
		s = int_to_string(num, buf + 24, base);
		j = 24 + buf - s;
		if(!width)
			width = j;
		else
			while(width > j)  {
				fputc(pad, f);
				i++;
				width--;
			}
		i += fwrite(s, 1, width, f);
		next:;
	}
	end:
	return i;
}
