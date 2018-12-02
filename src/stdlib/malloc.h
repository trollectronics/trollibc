#ifndef MALLOC_H_
#define MALLOC_H_

/*Macros*/
#define ALIGN(x) ((x + (sizeof(long) - 1)) & ~(sizeof(long) - 1))
#define ALIGNWITH(x, y) ((x + ((y) - 1)) & ~((y) - 1))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

#ifndef STRATEGY
#define STRATEGY 4
#endif

/*This is all the difference between best fit and worst fit*/
#if STRATEGY == 3
#define FIT_COMPARE >
#else
#define FIT_COMPARE <
#endif

#ifndef NRQUICKLISTS
#define NRQUICKLISTS 4
#endif

typedef struct Header Header;
struct Header {
	size_t size;
	Header *next;
};

extern Header *freelist[NRQUICKLISTS + 1];

#endif
