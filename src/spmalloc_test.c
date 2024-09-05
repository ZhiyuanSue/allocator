#include <inc.h>
#include <types.h>
#include <spmalloc.h>
#define NR_CHUNK      12
#define NR_ITERATIONS 10000
#define NR_VICTIM     100
#define NR_PTRS       10000
void* ptrs[NR_PTRS];
int ptrs_id[NR_PTRS];
static u64 next = 10086;
// I have to tell you that this rand function might not good enough for a larger
// range test
static u64 sprand()
{
        next = ((((u64)next * 1103515245 + 12345) / 65536) % 32768);
        return next;
}
static bool check_usable_victim(int victim, int curr_max)
{
        for (int i = 0; i < curr_max; i++)
                if (ptrs_id[i] == victim)
                        return false;
        return true;
}
void spmalloc_test(void)
{
        /*if no time module support ,just ignore the clock part*/
        clock_t start, end;
        double total_time = 0.0;
        spmalloc_init();
        for (int i = 0; i < NR_ITERATIONS; i++) {
                if (!(i % 100))
                        printf("iteration %d\n", i);
                /*first alloc all with a rand size*/
                start = clock();
                for (int j = 0; j < NR_PTRS; j++) {
                        ptrs[j] = spmalloc(obj_size[sprand() % NR_CHUNK]);
                        if (!ptrs[j])
                                goto error;
                }

                /*choose some victim pointer
                        free them all
                        record the ptrs ids
                        and alloc them again all with a rand size*/
                for (int j = 0; j < NR_VICTIM; j++) {
                        /*choose victim number*/
                        int victim_number = sprand() % NR_VICTIM;
                        /*free them all*/
                        for (int k = 0; k < victim_number; k++) {
                                int victim;
                                do {
                                        victim = sprand() % NR_PTRS;
                                } while (!check_usable_victim(victim, k));
                                /*use ptrs id to record the victims*/
                                ptrs_id[k] = victim;
                                spfree(ptrs[victim]);
                        }
                        /*realloc them all*/
                        for (int k = 0; k < victim_number; k++) {
                                ptrs[ptrs_id[k]] =
                                        spmalloc(obj_size[sprand() % NR_CHUNK]);
                                if (!ptrs[ptrs_id[k]])
                                        goto error;
                        }
                }
                /*free all the ptrs*/
                for (int j = 0; j < NR_PTRS; j++) {
                        spfree(ptrs[j]);
                }
                end = clock();
                total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("[ TEST ] total time used is %lf\n", total_time);

        printf("[ TEST ] spmalloc test pass!\n");
        return;
error:
        printf("[ ERROR ] spmalloc fail\n");
        return;
}