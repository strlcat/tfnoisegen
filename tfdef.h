#ifndef _THREEFISH_NOISE_GENERATOR_CIPHER_DEFINITIONS_HEADER
#define _THREEFISH_NOISE_GENERATOR_CIPHER_DEFINITIONS_HEADER

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <stddef.h>
#include <stdint.h>
#include "machdefs.h"

#if defined(MACHINE_64BIT)
#define TFNG_UNIT_TYPE uint64_t
#define TFNG_NR_BLOCK_BITS 256
#define TFNG_NR_KEY_BITS 512
#else
#define TFNG_UNIT_TYPE uint32_t
#define TFNG_NR_BLOCK_BITS 128
#define TFNG_NR_KEY_BITS 256
#endif

#define TFNG_NR_BLOCK_UNITS 4
#define TFNG_NR_KEY_UNITS 8

#define TFNG_BYTE_TYPE uint8_t
#define TFNG_SIZE_UNIT (sizeof(TFNG_UNIT_TYPE))
#define TFNG_BLOCK_SIZE (TFNG_SIZE_UNIT * TFNG_NR_BLOCK_UNITS)
#define TFNG_KEY_SIZE (TFNG_SIZE_UNIT * TFNG_NR_KEY_UNITS)

#define TFNG_TO_BITS(x) ((x) * 8)
#define TFNG_FROM_BITS(x) ((x) / 8)
#define TFNG_MAX_BITS TFNG_NR_BLOCK_BITS
#define TFNG_UNIT_BITS (TFNG_SIZE_UNIT * 8)

void tfng_encrypt_rawblk(TFNG_UNIT_TYPE *O, const TFNG_UNIT_TYPE *I, const TFNG_UNIT_TYPE *K);

#endif
