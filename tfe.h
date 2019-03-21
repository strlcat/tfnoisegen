#ifndef _TFNG_STREAM_CIPHER_DEFS
#define _TFNG_STREAM_CIPHER_DEFS

#include "tfdef.h"

struct tfnge_stream {
	TFNG_UNIT_TYPE key[TFNG_NR_KEY_UNITS];
	TFNG_UNIT_TYPE iv[TFNG_NR_BLOCK_UNITS];
	TFNG_BYTE_TYPE carry_block[TFNG_BLOCK_SIZE];
	size_t carry_bytes;
};

void tfnge_init(struct tfnge_stream *tfe, const void *key);
void tfnge_init_iv(struct tfnge_stream *tfe, const void *key, const void *iv);
void tfnge_emit(void *dst, size_t szdst, struct tfnge_stream *tfe);

#endif
