#include <kstacks.h>
#include <stdio.h>

int main(void) {
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
