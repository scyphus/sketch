/*_
 * Copyright 2010 Scyphus Solutions Co.,Ltd.  All rights reserved.
 *
 * Authors:
 *      Hirochika Asai  <asai@scyphus.co.jp>
 */

/* $Id: hash.c,v e8ba308c689d 2010/10/08 03:29:52 Hirochika $ */

#include <stdlib.h>
#include <stdint.h>

#include "hash.h"

#define PRIME           ((1L<<61) - 1)
#define K_ORDER         10

#define LOW(x) ((x) & 0xffffffff)
#define HIGH(x) ((x) >> 32)

static __inline__ int _init_table(hash_t *, unsigned int);

/*
 * Initialize hash instance
 */
hash_t *
hash_init(hash_t *h, unsigned int seed)
{
    if ( NULL == h ) {
        /* Allocate new instance */
        h = malloc(sizeof(hash_t));
        if ( NULL == h ) {
            /* Memory error */
            return NULL;
        }
        h->_need_to_free = 1;
    } else {
        h->_need_to_free = 0;
    }

    h->seed = seed;
    (void)_init_table(h, seed);

    return h;
}

/*
 * Release hash instance
 */
void
hash_release(hash_t *h)
{
    if ( h->_need_to_free ) {
        free(h);
    }
}


static __inline__ uint64_t
_mult_add_prime(uint32_t x, uint64_t a, uint64_t b)
{
    uint64_t a0;
    uint64_t a1;
    uint64_t c0;
    uint64_t c1;
    uint64_t c;

    a0 = LOW(a) * x;
    a1 = HIGH(a)* x;
    c0 = a0 + (a1<<32);
    c1 = (a0>>32) + a1;
    c = (c0&PRIME) + (c1>>29) + b;

    return c;
}

static __inline__ int
_init_table(hash_t *h, unsigned int seed)
{
    uint64_t a0[K_ORDER];
    uint64_t a1[K_ORDER];
    uint64_t a2[K_ORDER];
    uint64_t cw0;
    uint64_t cw1;
    uint64_t cw2;
    int i;
    int j;

    /* Initialize each table */
    for ( i = 0; i < TABLE_SIZE; i++ ) {
        h->T0[i] = 0;
        h->T1[i] = 0;
        h->T2[i] = 0;
    }

    srand(seed);

    for ( i = 0; i < TABLE_SIZE; i++ ) {
        for ( j = 0; j < K_ORDER; j++ ) {
            a0[j] = ((((uint64_t)rand())<<32) + ((uint64_t)rand())) % PRIME;
            a1[j] = ((((uint64_t)rand())<<32) + ((uint64_t)rand())) % PRIME;
            a2[j] = ((((uint64_t)rand())<<32) + ((uint64_t)rand())) % PRIME;
        }

        /* CWtrick */
        cw0 = a0[0];
        cw1 = a1[0];
        cw2 = a2[0];
        for ( j = 1; j < K_ORDER; j++ ) {
            cw0 = _mult_add_prime(j, cw0, a0[j]);
            cw1 = _mult_add_prime(j, cw1, a1[j]);
            cw2 = _mult_add_prime(j, cw2, a2[j]);
        }
        cw0 = ((cw0&PRIME) + (cw0>>61)) % PRIME;
        cw1 = ((cw1&PRIME) + (cw1>>61)) % PRIME;
        cw2 = ((cw2&PRIME) + (cw2>>61)) % PRIME;

        /* Set to tables */
        h->T0[i] = cw0;
        h->T1[i] = cw1;
        h->T2[i] = cw2;
    }

    return 0;
}

static __inline__ uint32_t
_hash32(uint32_t x, uint64_t *T0, uint64_t *T1, uint64_t *T2)
{
    uint32_t x0;
    uint32_t x1;
    uint32_t x2;

    x0 = x & 0xffff;
    x1 = x>>16;
    x2 = x0 + x1;

    /* compress32 */
    x2 = 2 - (x2>>16) + (x2&0xffff);

    return T0[x0] ^ T1[x1] ^ T2[x2];
}

uint32_t
hash32(hash_t *h, uint32_t x)
{
    return  _hash32(x, h->T0, h->T1, h->T2);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
