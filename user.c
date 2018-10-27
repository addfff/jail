#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main()
{
    /*Spawn a child to run the program.*/
    pid_t pid=fork();
    if (pid==0) { /* child process */
        //static char *argv[]={"echo","Foo is my name.",NULL};
        //execv("/bin/echo",argv);
        //exit(127); /* only if execv fails */
	
	execv("cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > /tmp/101-randstring");
	execv("UF=`cat /tmp/101-randstring`");
	execv("md5 -q /tmp/101-randstring");
	execv("UL=`md5 -q /tmp/101-randstring`"); 
	
	exit(127);
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }
    return 0;
}
