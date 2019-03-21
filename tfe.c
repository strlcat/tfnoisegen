#include <string.h>
#include "tfdef.h"
#include "tfe.h"

void tfnge_init_iv(struct tfnge_stream *tfe, const void *key, const void *iv)
{
	memset(tfe, 0, sizeof(struct tfnge_stream));
	memcpy(tfe->key, key, TFNG_KEY_SIZE);
	if (iv) memcpy(tfe->iv, iv, TFNG_BLOCK_SIZE);
	tfe->carry_bytes = 0;
}

void tfnge_init(struct tfnge_stream *tfe, const void *key)
{
	tfnge_init_iv(tfe, key, NULL);
}

void tfnge_emit(void *dst, size_t szdst, struct tfnge_stream *tfe)
{
	TFNG_BYTE_TYPE *udst = dst;
	size_t sz = szdst;

	if (!dst && szdst == 0) {
		memset(tfe, 0, sizeof(struct tfnge_stream));
		return;
	}

	if (tfe->carry_bytes > 0) {
		if (tfe->carry_bytes > szdst) {
			memcpy(udst, tfe->carry_block, szdst);
			memmove(tfe->carry_block, tfe->carry_block+szdst, tfe->carry_bytes-szdst);
			tfe->carry_bytes -= szdst;
			return;
		}

		memcpy(udst, tfe->carry_block, tfe->carry_bytes);
		udst += tfe->carry_bytes;
		sz -= tfe->carry_bytes;
		tfe->carry_bytes = 0;
	}

	if (sz >= TFNG_BLOCK_SIZE) {
		do {
			tfng_encrypt_rawblk(tfe->iv, tfe->iv, tfe->key);
			memcpy(udst, tfe->iv, TFNG_BLOCK_SIZE);
			udst += TFNG_BLOCK_SIZE;
		} while ((sz -= TFNG_BLOCK_SIZE) >= TFNG_BLOCK_SIZE);
	}

	if (sz) {
		tfng_encrypt_rawblk(tfe->iv, tfe->iv, tfe->key);
		memcpy(udst, tfe->iv, sz);
		udst = (TFNG_BYTE_TYPE *)tfe->iv;
		tfe->carry_bytes = TFNG_BLOCK_SIZE-sz;
		memcpy(tfe->carry_block, udst+sz, tfe->carry_bytes);
	}
}
