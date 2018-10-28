#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) 
{
	int ret;
	printf("Calling execl....\n");
	/* ret = execl("/bin/sh", "sh", "user.sh", NULL);*/
	ret = execl("/usr/local/bin/mysql", "mysql", "--user=j1", "--password=7PfA9oAwps", "j1", "<", "0013-insertintotable.sql", NULL);

	printf("Failed execl.. ret = %d\n*, ret");

	return 0;
}
