#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) 
{
	int ret;
	printf("Calling execl....\n");
	ret = execl("/bin/sh", "sh", "contoh.sh", NULL);

	printf("Failed execl.. ret = %d\n*, ret");

	return 0;
}
