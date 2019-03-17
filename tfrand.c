#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "tfdef.h"
#include "tfprng.h"

#define DATASIZE 65536

static char data[DATASIZE];
static char key[TF_KEY_SIZE];

int main(int argc, char **argv)
{
	int fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd != -1) {
		read(fd, key, sizeof(key));
		close(fd);
	}

	tf_prng_seedkey(key);
	while (1) {
		tf_prng_genrandom(data, DATASIZE);
		if (write(1, data, DATASIZE) == -1) return 1;
	}
	tf_prng_seedkey(NULL);

	return 0;
}
