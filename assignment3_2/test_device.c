#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	char buf[50];
	int i = 0;
	memset(buf,50,0);
	scanf("%s", buf);
	printf("%s\n", buf);
	int fp = open("/dev/mydevice_driver", O_RDWR);
	write(fp, buf, strlen(buf));
	read(fp, &buf, sizeof(buf) );
	printf("%s\n", buf);
	return 0;
}