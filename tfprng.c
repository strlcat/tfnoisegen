#include <string.h>
#include "tfe.h"
#include "tfprng.h"

struct tfng_prng_data {
	struct tfnge_stream tfe;
	short init;
};

struct tfng_prng_data tfng_prng_sdata;

size_t tfng_prng_datasize(void)
{
	return sizeof(struct tfng_prng_data);
}

void tfng_prng_seedkey_r(void *sdata, const void *skey)
{
	TFNG_UNIT_TYPE k[TFNG_NR_KEY_UNITS];
	struct tfng_prng_data *rprng = sdata;

	memset(rprng, 0, tfng_prng_datasize());
	if (!skey) return;

	memcpy(k, skey, TFNG_KEY_SIZE);
	tfnge_init(&rprng->tfe, k);
	rprng->init = 1;

	memset(k, 0, TFNG_KEY_SIZE);
}

void tfng_prng_seedkey(const void *skey)
{
	tfng_prng_seedkey_r(&tfng_prng_sdata, skey);
}

void tfng_prng_genrandom_r(void *sdata, void *result, size_t need)
{
	struct tfng_prng_data *rprng = sdata;
	memset(result, 0, need);
	tfnge_emit(result, need, &rprng->tfe);
}

void tfng_prng_genrandom(void *result, size_t need)
{
	tfng_prng_genrandom_r(&tfng_prng_sdata, result, need);
}

void tfng_prng_seed_r(void *sdata, TFNG_UNIT_TYPE seed)
{
	TFNG_UNIT_TYPE k[TFNG_NR_KEY_UNITS];
	struct tfng_prng_data *rprng = sdata;
	size_t x;

	memset(rprng, 0, tfng_prng_datasize());
	for (x = 0; x < TFNG_NR_KEY_UNITS; x++) k[x] = seed;
	tfnge_init(&rprng->tfe, k);
	rprng->init = 1;

	memset(k, 0, TFNG_KEY_SIZE);
}

void tfng_prng_seed(TFNG_UNIT_TYPE seed)
{
	tfng_prng_seed_r(&tfng_prng_sdata, seed);
}

TFNG_UNIT_TYPE tfng_prng_random_r(void *sdata)
{
	struct tfng_prng_data *rprng = sdata;
	TFNG_UNIT_TYPE r;

	if (!rprng->init) return 0;

	tfnge_emit(&r, sizeof(r), &rprng->tfe);
	return r;
}

TFNG_UNIT_TYPE tfng_prng_random(void)
{
	return tfng_prng_random_r(&tfng_prng_sdata);
}

TFNG_UNIT_TYPE tfng_prng_range_r(void *sdata, TFNG_UNIT_TYPE s, TFNG_UNIT_TYPE d)
{
	TFNG_UNIT_TYPE c = tfng_prng_random_r(sdata);
	if (d <= s) return s;
	return TFNG_PRNG_RANGE(c, TFNG_UNIT_TYPE, s, d);
}

TFNG_UNIT_TYPE tfng_prng_range(TFNG_UNIT_TYPE s, TFNG_UNIT_TYPE d)
{
	return tfng_prng_range_r(&tfng_prng_sdata, s, d);
}
