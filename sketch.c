/*_
 * Copyright 2010 Scyphus Solutions Co.,Ltd.  All rights reserved.
 *
 * Authors:
 *      Hirochika Asai  <asai@scyphus.co.jp>
 */

/* $Id: sketch.c,v e8ba308c689d 2010/10/08 03:29:52 Hirochika $ */

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#define N_HASH 16

int
main(int argc, const char *const argv[], const char *const envp[])
{
    hash_t *h[N_HASH];
    int i;
    uint32_t x;

    /* Initialize hash tables */
    for ( i = 0; i < N_HASH; i++ ) {
        h[i] = hash_init(NULL, 1023 + i);
        if ( NULL == h[i] ) {
            /* Memory error */
            return EXIT_FAILURE;
        }
    }

    for ( x = 0; x < 100; x++ ) {
        for ( i = 0; i < N_HASH; i++ ) {
            if ( i != 0 ) {
                printf(" ");
            }
            /*printf("%02x", hash32(h[i], x)&0x1f);*/
            printf("%08x", hash32(h[i], x));
        }
        printf("\n");
    }

    /* Release */
    for ( i = 0; i < N_HASH; i++ ) {
        hash_release(h[i]);
    }

    return 0;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
