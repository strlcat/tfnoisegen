#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "tfdef.h"
#include "tfprng.h"

#define DATASIZE 65536

static char data[DATASIZE];
static char key[TFNG_KEY_SIZE];

int main(int argc, char **argv)
{
	int fd;
	char *randsource;

	if (argc > 1 && argv[1]) {
		if (!strcmp(argv[1], "-")) {
			fd = 0;
			goto _stdinrnd;
		}
		randsource = argv[1];
	}
	else randsource = "/dev/urandom";

	fd = open(randsource, O_RDONLY);
	if (fd != -1) {
_stdinrnd:	read(fd, key, sizeof(key));
		if (fd != 0) close(fd);
	}
	else {
		perror(argv[1]);
		return 1;
	}

	tfng_prng_seedkey(key);
	while (1) {
		tfng_prng_genrandom(data, DATASIZE);
		if (write(1, data, DATASIZE) == -1) return 1;
	}
	tfng_prng_seedkey(NULL);

	return 0;
}
