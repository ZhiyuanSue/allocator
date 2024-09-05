# spmalloc
this is a simple memory allocator

I want to add a memory allocator for [shampoos project](https://github.com/ZhiyuanSue/Shampoos)

so I first try to realize an allocator at user level

and I will also give a test of this allocator

I also hope this work can be reuse by others.

so the functions I used from C std lib will only about the followings

 - printf: to print some thing
 - malloc: in order to get a huge memory from system, and I will also test this function as a comparation of spmalloc
 - free: free the memory, also a comparation

# usage
use default to use glibc malloc
```
make DEFAULT=true
```

just only a make can run the spmalloc

```
make
```