#ifndef INCLUDE_ALLOCATOR_H
#define INCLUDE_ALLOCATOR_H

void* mem_alloc(int32_t size);
void* mem_realloc(void *ptr, int32_t size);
void mem_free(void *ptr);

#endif