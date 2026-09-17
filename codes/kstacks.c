#include "kstacks.h"
#include <stdlib.h>

void kcreate(kstack_t *sp) {
    if (sp == NULL) return;
    if (sp->size == 0) return;
    sp->addr = malloc(sp->size * sizeof(uint8_t));
    if (sp->addr == NULL) return;
    sp->top = 0;
    sp->flag = K_OK;
}

void kfree(kstack_t *sp) {
    if (sp == NULL) return;
    free(sp->addr);
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
