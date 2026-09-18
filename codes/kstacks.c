#include "kstacks.h"
#include <stdlib.h>

static k_malloc_t  k_malloc  = NULL;
static k_free_t    k_free    = NULL;
static k_realloc_t k_realloc = NULL;

k_bool kinit_allocator(k_allocator_t *m) {
    if (m == NULL || m->k_malloc == NULL || m->k_free == NULL) {
        return K_FALSE;
    }
    k_malloc  = m->k_malloc;
    k_free    = m->k_free;
    k_realloc = m->k_realloc;   /* maybe NULL */
    return K_TRUE;
}

void kcreate(kstack_t *sp) {
    if(k_malloc == NULL || k_free == NULL) return;
    if (sp == NULL) return;
    if (sp->size == 0) return;
    sp->addr = k_malloc(sp->size * sizeof(uint8_t));
    if (sp->addr == NULL) return;
    sp->top = 0;
    sp->flag = K_OK;
}

void kfree(kstack_t *sp) {
    if (sp == NULL) return;
    k_free(sp->addr);
    sp->addr = NULL;
    sp->top = 0;
    sp->id = 0;
    sp->size = 0;
    sp->flag = K_OK;
}

void kpush(kstack_t *sp, uint8_t value) {
    if (sp == NULL) return;
    if (sp->top >= sp->size) {
        sp->flag = ERR_OVERFLOW;
        return;
    }
    sp->addr[sp->top] = value;
    sp->top++;
}

int16_t kpop(kstack_t *sp) {
    if (sp == NULL) return NO_SP;
    if (sp->top == 0) {
        sp->flag = ERR_UNDERFLOW;
        return SP_TOP_IS_0;
    }
    sp->top--;
    return sp->addr[sp->top];
}

int16_t kpeek(kstack_t *sp) {
    if (sp == NULL) return NO_SP;
    if (sp->top == 0) return SP_TOP_IS_0;
    return sp->addr[sp->top - 1];
}

void kexpand(kstack_t *sp, uint64_t new_size) {
    if(k_realloc == NULL) return;
    if (sp == NULL) return;
    if (new_size <= sp->size) return;
    uint8_t *new_addr = realloc(sp->addr, new_size);
    if (new_addr == NULL) {
        sp->flag = ERR_OVERFLOW;
        return;
    }
    sp->addr = new_addr;
    sp->size = new_size;
}

uint64_t kcount(kstack_t *sp, int *err_) {
    if (err_ != NULL) *err_ = K_OK;
    if (sp == NULL) {
        if (err_ != NULL) *err_ = NO_SP;
        return 0;
    }
    return sp->top;
}
