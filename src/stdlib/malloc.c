#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "malloc.h"

#define PAGE_SIZE getpagesize()

/**
 * malloc - Implementation of malloc et al
 * malloc.c - Memory allocation library functions
 * @author Axel Isaksson <axelis@kth.se>
 * @copyright MIT/X11 License, see COPYING
 * 
 * Contains the library functions malloc(3), free(3) and realloc(3).
 * Several algorithms can be used for allocation, see README
 * 
 */

void *sbrk(intptr_t increment);

/*Pointer to the linked lists with free blocks*/
Header *freelist[NRQUICKLISTS + 1];
/*Keep statistics of total used mem*/
size_t malloc_used_mem = 0;


/**
 * Allocate a new block on the heap from the system.
 * The block will be aligned to a page boundary and the block
 * size will be rounded upwards to the next page.
 * 
 * @param size Size in bytes excluding header
 * @return Newly allocated block of ram, beginning with a header
 */
static Header *getmore(size_t size) {
	Header *header;
	
	size = ALIGNWITH(size + sizeof(Header), PAGE_SIZE);
	malloc_used_mem += size;
	header = sbrk(size);
	if(header == (void *) - 1)
		return NULL;
	header->size = size - sizeof(Header);
	
	return header;
}
/**
 * Allocate memory
 * 
 * @param size Size in bytes to be allocated
 * @return Pointer to avaible block of memory, or NULL on failure
 */
void *real_malloc(size_t size) {
	Header **iter, *header;
	#if STRATEGY != 1
	Header **tmp;
	#endif
	#if STRATEGY == 4
	int list, i;
	
	for(list = 0; list < NRQUICKLISTS && size > (8 << list); list++);
	#endif
	
	if(!size)
		return NULL;
	
	for(;;) {
		#if STRATEGY == 1
		/*First fit*/
		for(iter = &freelist[NRQUICKLISTS]; *iter && (*iter)->size < size; iter = &(*iter)->next);
		#elif STRATEGY == 4
		/*Quick fit*/
		for(iter = &freelist[list]; *iter && (*iter)->size < size; iter = &(*iter)->next);
		#else
		/*Best/worst fit*/
		tmp = NULL;
		for(iter = &freelist[NRQUICKLISTS]; *iter; iter = &(*iter)->next)
			if((*iter)->size >= size && (!tmp || (*iter)->size FIT_COMPARE (*tmp)->size))
				tmp = iter;
		if(tmp)
			iter = tmp;
		#endif
		if(*iter) {
			header = *iter;
			if(ALIGN(header->size) > (ALIGN(size) + sizeof(Header))) {
				/*Split the block up*/
				Header *newheader = (Header *)(((char *) (header + 1)) + ALIGN(size));
				newheader->size = ALIGN(header->size) - (ALIGN(size) + sizeof(Header));
				header->size = ALIGN(size);
				newheader->next = header->next;
				*iter = newheader;
			} else
				*iter = header->next;
			
			return header + 1;
		} else {
			/*No free, large enough blocks availble, get more from system*/
			if((header = getmore(size))) {
				#if STRATEGY == 4
				if(list < NRQUICKLISTS) {
					/*Split quicklist-blocks into smaller pieces at once*/
					int sz = header->size + sizeof(Header);
					tmp = &header;
					for(i = 0; i < sz/((8 << list) + sizeof(Header)); i++) {
						(*tmp)->size = (8 << list);
						(*tmp)->next = (Header *) (((char *) *tmp) + (8 << list) + sizeof(Header));
						tmp = &(*tmp)->next;
					}
					*tmp = freelist[list];
					freelist[list] = header;
					continue;
				}
				#endif
				free(header + 1);
			} else
				return NULL;
		}
	}
}
