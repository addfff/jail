#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000
int sh();
int proga();
int progb();
int main(int argc, char *argv[]) 
{

	int ret;

	if (fork()) {
		if (fork()){
			ret = progb();
		}

		else {
			ret = proba();
		}
	}
	else {
		sleep(1); 
		ret = sh();
	}
	return 0;
}

int sh()
{
	int ret;
        printf("Calling execl....\n");
        ret = execl("/bin/sh", "sh", "/tmp/user.sh", NULL);
        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}

int proga()
{
        int ret;
        printf("Calling execl....\n");
        ret = execl("/tmp/proga", "proga", NULL);
        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}


int progb()
{
        int ret;
        printf("Calling execl....\n");
        ret = execl("/root/progb", "progb", NULL);

        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}
