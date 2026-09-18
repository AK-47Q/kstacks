#include <kstacks.h>
#include <stdio.h>

int main(void) {
    kallocator_t x = {.k_malloc = malloc, .k_free = free, .k_realloc = NULL};
    if(kinit_allocator(&x) == K_FALSE) {
        printf("\nError: kinit_allocator didnt work.\n");
        return 1;
    }
    kstack_t t;
    t.id = 0;
    t.size = 24;
    kcreate(&t);

    kpush(&t, 5);

    int g = (int)kpop(&t);
    printf("\n %i\n", g);

    kfree(&t);
    return 0;
}
