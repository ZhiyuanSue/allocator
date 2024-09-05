#include <inc.h>
#include "types.h"
#include <rb_tree.h>
void spmalloc_init();
void* spmalloc(size_t size);
void spfree(void* p);