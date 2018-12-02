/**
 * Change the size of an allocated memory block.
 * Can both grow and shrink. Will allocate a new block,
 * move the data and free the old block.
 * 
 * @param ptr Pointer to a previously allocated block of memory
 * @param size New requested size of the block
 * @return Pointer to the new memory block, or NULL on failure
 */
void *realloc(void *ptr, size_t size) {
	void *tmp;
	Header *header;
	
	if(!ptr)
		return malloc(size);
	
	if(!size) {
		free(ptr);
		return NULL;
	}
	/*Should directly split block when shrinking without malloc+copy, but too lazy*/
	tmp = malloc(size);
	header = ((Header *) ptr) - 1;
	memcpy(tmp, ptr, MIN(header->size, size));
	free(ptr);
	return tmp;
}
