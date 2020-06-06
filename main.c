#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "root_oemkey.h"

unsigned char binArray[OEM_PUBK_SZ] = {OEM_PUBK};

int main(void) {

	int i = 0;
	int fd = -1;


	for (i = 0; i < OEM_PUBK_SZ; i++) {\
		if (i % 8 == 0)
			printf("\n");

		printf("%02X", binArray[i]);
		write(fd, binArray + i, 1);
	}

	printf("\n\n");

	fd = open("out.bin", O_WRONLY | O_CREAT);
	if (fd == -1) {
		printf("open out.bin file error\n");
		return -1;
	} else
		printf("open out.bin file success\n");
	write(fd, binArray, OEM_PUBK_SZ);
	close(fd);

	printf("data write to out.bin success\n");
}
