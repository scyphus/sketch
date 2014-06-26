/*_
 * Copyright 2010 Scyphus Solutions Co.,Ltd.  All rights reserved.
 *
 * Authors:
 *      Hirochika Asai  <asai@scyphus.co.jp>
 */

/* $Id$ */

#ifndef _HASH_H
#define _HASH_H

#include <stdint.h>

#define TABLE_SIZE      0x20000

/* hash function instance */
typedef struct _hash {
    unsigned int seed;
    uint64_t T0[TABLE_SIZE];
    uint64_t T1[TABLE_SIZE];
    uint64_t T2[TABLE_SIZE];
    /* need to free on release? */
    int _need_to_free;
} hash_t;


#ifdef __cplusplus
extern "C" {
#endif

    hash_t * hash_init(hash_t *, unsigned int);
    void hash_release(hash_t *);
    uint32_t hash32(hash_t *, uint32_t);

#ifdef __cplusplus
}
#endif

#endif /* _HASH_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
