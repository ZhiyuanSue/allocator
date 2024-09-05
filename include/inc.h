#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#define container_of(ptr, type, member)                            \
        ({                                                         \
                const typeof(((type *)0)->member) *__mptr = (ptr); \
                (type *)((char *)__mptr - offsetof(type, member)); \
        })
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void rb_tree_test(void);
void spmalloc_test(void);

static inline void* get_free_pages(int order){
	size_t size=(4096<<order);
	void* p=malloc(size);
	return p;
}
static inline void free_pages(void* p){
	if(p)
		free(p);
}