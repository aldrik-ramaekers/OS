// Placeholder allocator untill I implement custom allocator.

void* mem_alloc(int32_t size)
{
   return malloc(size);
}

void* mem_realloc(void *ptr, int32_t size)
{
   return realloc(ptr, size);
}

void mem_free(void *ptr)
{
   free(ptr);
}