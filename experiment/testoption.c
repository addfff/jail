#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) 
{
	int ret;
	printf("Calling execl....\n");
        /* ret = execl("/bin/ls", "ls", "-lh", "|wc",NULL); */
	ret = execl("/usr/local/bin/mysql", "mysql", "rawdb","-u", "root","--password=toor", "-e", "SHOW TABLES", NULL);
	printf("Failed execl.. ret = %d\n*, ret");

	return 0;
}
