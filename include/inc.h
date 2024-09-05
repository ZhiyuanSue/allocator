#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#define container_of(ptr, type, member)                            \
        ({                                                         \
                const typeof(((type *)0)->member) *__mptr = (ptr); \
                (type *)((char *)__mptr - offsetof(type, member)); \
        })
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void rb_tree_test(void);