#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	assert(argc > 1);
	char buf[50] = "abcd";
	int i = 0;
	int fp = open("/dev/mydevice_driver", O_RDWR);
	printf("%s\n", argv[1]);
	write(fp, argv[1], strlen(argv[1]));
	int x = 5;
	memset(buf,0,50);
	read(fp, &buf, 50);
	printf("%s\n", buf);
	close(fp);
	return 0;
}
