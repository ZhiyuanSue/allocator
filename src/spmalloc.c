#include <spmalloc.h>

void spmalloc_init()
{
#ifndef DEFAULT
#endif
}
void* spmalloc(size_t size)
{
#ifdef DEFAULT
        return malloc(size);
#else

#endif
}
void spfree(void* p)
{
#ifdef DEFAULT
        free(p);
#else

#endif
}