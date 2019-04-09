#ifndef _TFNG_PRNG_DEFINITIONS_HEADER
#define _TFNG_PRNG_DEFINITIONS_HEADER

#include <stdlib.h>
#include "tfdef.h"

#define TFNG_PRNG_KEY_SIZE TFNG_KEY_SIZE
#define TFNG_PRNG_SIZE_UNIT TFNG_SIZE_UNIT
#define TFNG_PRNG_RANGE(C, T, S, D) (S + C / ((T)~0 / (D - S + 1) + 1))

size_t tfng_prng_datasize(void);
void tfng_prng_seedkey_r(void *sdata, const void *skey);
void tfng_prng_seedkey(const void *skey);
void tfng_prng_genrandom_r(void *sdata, void *result, size_t need);
void tfng_prng_genrandom(void *result, size_t need);
void tfng_prng_seed_r(void *sdata, TFNG_UNIT_TYPE seed);
void tfng_prng_seed(TFNG_UNIT_TYPE seed);
TFNG_UNIT_TYPE tfng_prng_random_r(void *sdata);
TFNG_UNIT_TYPE tfng_prng_random(void);
TFNG_UNIT_TYPE tfng_prng_range_r(void *sdata, TFNG_UNIT_TYPE s, TFNG_UNIT_TYPE d);
TFNG_UNIT_TYPE tfng_prng_range(TFNG_UNIT_TYPE s, TFNG_UNIT_TYPE d);

#endif
