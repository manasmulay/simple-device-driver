#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	// assert(argc > 1);
	char buf[50] = "abcd";
	int i = 0;
	int fp = open("/dev/mydevice_driver", O_RDWR);
	printf("%s\n", buf);
	write(fp, &buf, strlen(buf));
	int x = 5;
	memset(buf,0,50);
	read(fp, &buf, 50);
	printf("%s\n", buf);
	close(fp);
	return 0;
}
