#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main( void ) {
	char *argv[3] = {"Command-line", ".", NULL};

	int pid = fork();

	if ( pid == 0 ) {
		execvp( "cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > /tmp/101-randstring", argv );
	}

	sleep(2);

	printf( "Finished executing the parent process\n"
	        " - the child won't get here--you will only see this once\n" );

	return 0;
}
