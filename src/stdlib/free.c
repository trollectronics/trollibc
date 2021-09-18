#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "malloc.h"

/**
 * Free allocated memory
 * 
 * @param ptr Pointer to a previously allocated block of memory
 */
void real_free(void *ptr) {
	Header **iter, *header;
	bool hasmerged = false;
	#if STRATEGY == 4
	int list;
	#endif
	if(!ptr)
		return;
	
	header = ((Header*) ptr) - 1;
	#if STRATEGY == 4
	for(list = 0; list < NRQUICKLISTS && header->size > (8 << list); list++);
	if(list < NRQUICKLISTS) {
		/*Quicklist blocks are not merged*/
		header->next = freelist[list];
		freelist[list] = header;
		return;
	}
	#endif
	
	redo:
	for(iter = &freelist[NRQUICKLISTS]; *iter; iter = &((*iter)->next)) {
		if(((char *) *iter) + (*iter)->size + sizeof(Header) == (void *) header) {
			/*Merge lower bound*/
			(*iter)->size += sizeof(Header) + header->size;
			header = *iter;
			*iter = (*iter)->next;
			goto redo;
		} else if(((char *) header) + sizeof(Header) + header->size == (void *) *iter) {
			/*Merge upper bound*/
			header->size += sizeof(Header) + (*iter)->size;
			header->next = (*iter)->next;
			*iter = header;
			hasmerged = true;
		}
	}
	if(!hasmerged) {
		header->next = freelist[NRQUICKLISTS];
		freelist[NRQUICKLISTS] = header;
	}
}
