#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000
int one();
int two();
int main(int argc, char *argv[]) 
{
	int ret;
   do{
	int pid = fork();

	if ( pid ==0) {
		ret = one();
	}
   	else{
		sleep(1); 
		ret = two();
	}
   }while(1);
	return 0;
}

int one()
{
	int ret;
        printf("Calling execl....\n");
        ret = execl("/bin/ls", "ls", "-l", NULL);
        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}

int two()
{
        int ret;
        printf("Calling execl....\n");
        ret = execl("/usr/bin/wc", "wc", "test.txt", NULL);
        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}


