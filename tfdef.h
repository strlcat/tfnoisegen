#ifndef _THREEFISH_CIPHER_DEFINITIONS_HEADER
#define _THREEFISH_CIPHER_DEFINITIONS_HEADER

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <stddef.h>
#include <stdint.h>

#define TF_UNIT_TYPE uint32_t

#define TF_NR_BLOCK_BITS 128
#define TF_NR_KEY_BITS 256
#define TF_NR_BLOCK_UNITS 4
#define TF_NR_KEY_UNITS 8

#define TF_BYTE_TYPE uint8_t
#define TF_SIZE_UNIT (sizeof(TF_UNIT_TYPE))
#define TF_BLOCK_SIZE (TF_SIZE_UNIT * TF_NR_BLOCK_UNITS)
#define TF_KEY_SIZE (TF_SIZE_UNIT * TF_NR_KEY_UNITS)

#define TF_TO_BITS(x) ((x) * 8)
#define TF_FROM_BITS(x) ((x) / 8)
#define TF_MAX_BITS TF_NR_BLOCK_BITS
#define TF_UNIT_BITS (TF_SIZE_UNIT * 8)

void tf_encrypt_rawblk(TF_UNIT_TYPE *O, const TF_UNIT_TYPE *I, const TF_UNIT_TYPE *K);

#endif
