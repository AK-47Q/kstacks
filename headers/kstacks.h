#ifndef KSTACKS_H
#define KSTACKS_H

#include "ktypes.h"

#define K_OK 0
#define ERR_OVERFLOW 1
#define ERR_UNDERFLOW 2
#define SP_TOP_IS_0 -1
#define NO_SP -2

typedef struct {
    k_malloc_t malloc;
    k_free_t free;
    k_realloc_t realloc; // optional, can be NULL if you dont want it
} kallocator_t;
typedef struct {
    uint32_t id;
    uint64_t size;
    uint8_t *addr;
    uint64_t top;
    uint8_t flag;
} kstack_t;

k_bool kinit_allocator(kallocator_t *alr);
void kcreate(kstack_t *sp);
void kfree(kstack_t *sp);
void kpush(kstack_t *sp, uint8_t value);
int16_t kpop(kstack_t *sp);
int16_t kpeek(kstack_t *sp);
void kexpand(kstack_t *sp, uint64_t new_size);
uint64_t kcount(kstack_t *sp, int *err_);

#endif
