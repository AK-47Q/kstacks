#ifndef KTYPES_H
#define KTYPES_H


typedef unsigned char k_bool;
#define K_FALSE ((k_bool)0)
#define K_TRUE  ((k_bool)1)

#define NULL ((void*)0)

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;

typedef unsigned long      size_t;

typedef void *(*k_malloc_t)(size_t s);
typedef void (*k_free_t)(void *m);
typedef void *(*k_realloc_t)(void *p, size_t n_s);
#endif
