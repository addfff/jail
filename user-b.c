#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mysql.h>
#include <time.h>

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
	MYSQL_RES *myresult;
        MYSQL_ROW row;
        MYSQL *myconnection, mysql;
        int state, ret;
        struct tm timeresultfromdb;
        struct tm timeresultnow;
	char buffer[0x100];
	time_t curtime;

	FILE *fp;
   	char str[MAXCHAR];
    	char* filename = "/tmp/0013-insertintotable.sql";


	mysql_init(&mysql);
	myconnection = mysql_real_connect(&mysql, "localhost", "root", "toor", "rawdb", 0, 0, 0);

	if (myconnection == NULL){
		printf(mysql_error(&mysql));
		return 1;
	}

	state = mysql_query(myconnection, "SELECT id, reg_date,firstkey FROM j1 ORDER BY reg_date DESC LIMIT 1");
	if (state != 0) {
		printf(mysql_error(myconnection));
		return 1;
	}

	myresult = mysql_store_result(myconnection);
	printf("Rows: %d\n", mysql_num_rows(myresult));
	while ( ( row = mysql_fetch_row(myresult)) != NULL){
		printf("Key inserted to Database >> id: %s, date:%s, key: %s\n",
		(row[0] ? row[0] : "NULL"),
		(row[1] ? row[1] : "NULL"),
		(row[2] ? row[2] : "NULL"));
		
		if(strptime(row[1],"%Y-%m-%d %H:%M:%S", &timeresultfromdb) == NULL)
			printf("\nstrptime failed\n");
		else{
			printf("tm_hour:  %d\n",timeresultfromdb.tm_hour);
          		printf("tm_min:  %d\n",timeresultfromdb.tm_min);
          		printf("tm_sec:  %d\n",timeresultfromdb.tm_sec);
          		printf("tm_mon:  %d\n",timeresultfromdb.tm_mon);
          		printf("tm_mday:  %d\n",timeresultfromdb.tm_mday);
          		printf("tm_year:  %d\n",timeresultfromdb.tm_year);
          		printf("tm_yday:  %d\n",timeresultfromdb.tm_yday);
          		printf("tm_wday:  %d\n",timeresultfromdb.tm_wday);
		}
	}

        curtime = time(NULL);
        if (curtime == -1){
        	perror("time()");
                return 1;
        }

        strftime(buffer, 0x100, "%a %m/%d/%Y %r", localtime(&curtime));
        if(strptime(buffer, "%a %m/%d/%Y %r", &timeresultnow)== NULL)
        	printf("\nstrptime failed\n");
        else{
		 printf("tm_hour:  %d\n",timeresultnow.tm_hour);
	          printf("tm_min:  %d\n",timeresultnow.tm_min);
	          printf("tm_sec:  %d\n",timeresultnow.tm_sec);
	          printf("tm_mon:  %d\n",timeresultnow.tm_mon);
	          printf("tm_mday:  %d\n",timeresultnow.tm_mday);
	          printf("tm_year:  %d\n",timeresultnow.tm_year);
	          printf("tm_yday:  %d\n",timeresultnow.tm_yday);
	          printf("tm_wday:  %d\n",timeresultnow.tm_wday);

        }
       	mysql_free_result(myresult);
	mysql_close(myconnection);
		

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\nCould not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);


        printf("Time Result 1 ===>minit: %d\n",timeresultfromdb.tm_min);
        printf("Time Result 2 ===>minit: %d\n",timeresultnow.tm_min);
        printf("Differnet =======>minit: %d\n",(timeresultnow.tm_min-timeresultfromdb.tm_min));

        if (!(timeresultnow.tm_min - timeresultfromdb.tm_min)){
                sleep(60);
                printf("will execute after one minute1\n");
        }
        else {
	        printf("\nCalling execl....\n");
        	ret = execl("/usr/local/bin/mysql", "mysql", "rawdb","-u", "j1","--password=7PfA9oAwps", "-e", str, NULL);
         	printf("\nFailed execl.. ret = %d\n*, ret");
	}
         return 0;
}
