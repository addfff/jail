#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 #define MAXCHAR 1000
int proga();
int sql();
int main(int argc, char *argv[]) 
{
	int ret;
 	if(fork()) {
		sleep(60);
		ret = proga();
	}
	sleep(1); 
	ret = sql();
	
	return 0;
}
 int proga()
{
	int ret;
        printf("\nCalling execl....\n");
        ret = execl("/root/proga", "proga", NULL);
        printf("Failed execl.. ret = %d\n*, ret");
         return 0;
}
 int sql()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/tmp/0013-insertintotable.sql";
     fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\nCould not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
         int ret;
        printf("\nCalling execl....\n");
        ret = execl("/usr/local/bin/mysql", "mysql", "rawdb","-u", "j1","--password=7PfA9oAwps", "-e", str, NULL);
         printf("\nFailed execl.. ret = %d\n*, ret");
         return 0;
}
