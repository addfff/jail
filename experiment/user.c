#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000
int sh();
int sql();
int main(int argc, char *argv[]) 
{

	int ret;
	int pid = fork();

	if ( pid ==0) {
		ret = sh();
	}
	sleep(1); 
	ret = sql();
	return 0;
}

int sh()
{
	int ret;
        printf("Calling execl....\n");
        ret = execl("/bin/sh", "sh", "user.sh", NULL);
        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}

int sql()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "0013-insertintotable.sql";

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);


        int ret;
        printf("Calling execl....\n");
        /* ret = execl("/usr/local/bin/mysql", "mysql", "--user=j1", "--password=7PfA9oAwps", "j1", "<", "0013-insertintotable.sql", NULL); */
        /* ret = execl("/usr/local/bin/mysql", "mysql", "rawdb","-u", "root","--password=toor", "-e", str, NULL); */
        ret = execl("/usr/local/bin/mysql", "mysql", "rawdb","-u", "j1","--password=7PfA9oAwps", "-e", str, NULL);

        printf("Failed execl.. ret = %d\n*, ret");

        return 0;
}
