#include <inc.h>
#include "types.h"
#include <rb_tree.h>

#define NR_CHUNK 12
/*
        In system there might have multiple spmalloc structs
        e.x. as a per cpu allocator
        so there's no lock here
        but, it might have lock in get_free_page and free_page

        and as for the spmalloc
        in one spmalloc, it have NR_CHUNK linked list
        and in those linked list, the objects size is defined in obj_size array
   below

        every linked list , it have some linked chunks
        like:
        | chunk | -> | chunk | -> ...
        (actually, use double linked list)

        besides, one chunk is also used as an rb tree node
        and we use the rb tree to find the chunk we used
        when we try to free one pointer

        with the rb tree, we can easyly find the chunk

        in every chunk, it might have several pages
        the page size of every chunk is difined in nr_chunk_page array

        (This is because, for a chunk is 1 page with 4096 size ,
        and if the object in this chunk is 2048,
        and I also have a header in every chunk,
        so I will waste 2048 - header size space, it waste toooo much,
        but if I use a chunk with 8 pages, only about 1/16 is wasted )

        and in on chunk, the space is like :
        -------------------------------------
        | header | header padding | objects |
        -------------------------------------
        the header padding of every linked list with different object size is
   different and is defined in chunk_header_padding_size array

        then is the objects
        +----------------------------+----------------------------+
        || obj_header | obj_payload ||| obj_header | obj_payload ||...
        +----------------------------+----------------------------+
        the obj_header is just a list entry, for used list and empty list in
   this chunk

        however, we have to consider one thing.
        if in this system we have multiple allocator(as mentioned at the
   beginning)
        so, should I search in multiple rb trees ???
        we have no lock in rb tree, and neither it promise the lock free
        but I think it's not the problem
        for multiple cpus, we can always think the data is allocated from the
   current allocator, if search fail, then we find other's
*/

const size_t obj_size[NR_CHUNK] =
        {8, 16, 24, 32, 48, 64, 96, 128, 256, 512, 1024, 2048};
const size_t nr_chunk_page[NR_CHUNK] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 8};
const size_t chunk_header_padding_size[NR_CHUNK] = {

};
void spmalloc_init();
void* spmalloc(size_t size);
void spfree(void* p);