/* https://docstore.mik.ua/orelly/weblinux2/mysql/ch12_01.htm */
/* https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_71/rtref/strpti.htm */
/* https://www.studytonight.com/c/programs/misc/display-current-date-and-time */
/* gcc -L/usr/local/lib/mysql -I/usr/local/include/mysql/ mysql-select-totime.c -lmysqlclient -lz */


#include <unistd.h>
#include <stdio.h>
#include <mysql.h>
#include <time.h>
  
int main(char **args) {
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *connection, mysql;
	int state;
	struct tm timeresult1;
	struct tm timeresult2;

    printf("\n\n\t\tStudytonight - Best place to learn\n\n\n");

    time_t t,now;   // not a primitive datatype
    time(&t);

    printf("\nThis program has been writeen at (date and time): %s", ctime(&t));

    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    sleep(1);
    now = time(NULL);
		printf("T1: Sleep and Now different %f seconds.\n", difftime(now, t));	
	
	
	sleep(1);
	/* connect to the MySQL database at localhost */
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,"localhost", "root", "toor", "rawdb", 0, 0, 0);

	/* check for a connection error */
	if (connection == NULL) {
		/* print the error message */
		printf(mysql_error(&mysql));
		return 1;
	}

	state = mysql_query(connection,"SELECT id, reg_date, firstkey FROM j1 ORDER BY reg_date DESC LIMIT 1");
	if (state != 0) {
		printf(mysql_error(connection));
		return 1;
	}

	/* must call mysql_store_result( ) before you can issue any other query calls */
    	result = mysql_store_result(connection);
    	printf("Rows: %d\n", mysql_num_rows(result));
    	/* process each row in the result set */
    	while ( ( row = mysql_fetch_row(result)) != NULL ) {
        	printf("Last Key inserted >> id: %s, date:%s, key: %s\n",
            	(row[0] ? row[0] : "NULL"),
            	(row[1] ? row[1] : "NULL"),
		(row[2] ? row[2] : "NULL"));
 		printf("\n===>Date=%s \n",row[1]);

        if(strptime(row[1], "%Y-%m-%d %H:%M:%S",&timeresult1) == NULL)
                printf("\nstrptime failed\n");
        else
        {
          printf("tm_hour:  %d\n",timeresult1.tm_hour);
          printf("tm_min:  %d\n",timeresult1.tm_min);
          printf("tm_sec:  %d\n",timeresult1.tm_sec);
          printf("tm_mon:  %d\n",timeresult1.tm_mon);
          printf("tm_mday:  %d\n",timeresult1.tm_mday);
          printf("tm_year:  %d\n",timeresult1.tm_year);
          printf("tm_yday:  %d\n",timeresult1.tm_yday);
          printf("tm_wday:  %d\n",timeresult1.tm_wday);
        }

 	}

/*	printf("Time Result 1 ===>minit:  %d\n",timeresult1.tm_min); */


  char buffer[0x100];
  time_t curtime;

  // Don't forget to check the return value !
  curtime = time(NULL);
                printf("T2: Sleep and Now different %f seconds.\n", difftime(curtime, t));
  if (curtime == -1)
  {
    perror("time()");
    return 1;
  }

  strftime(buffer,0x100,"%M",localtime(&curtime));
  printf("(NOW) minutes: %s\n", buffer);

  strftime(buffer,0x100,"%a %m/%d/%Y %r",localtime(&curtime));
 if(strptime(buffer, "%a %m/%d/%Y %r",&timeresult2) == NULL)
          printf("\nstrptime failed\n");
   else
   {
          printf("tm_hour:  %d\n",timeresult2.tm_hour);
          printf("tm_min:  %d\n",timeresult2.tm_min);
          printf("tm_sec:  %d\n",timeresult2.tm_sec);
          printf("tm_mon:  %d\n",timeresult2.tm_mon);
          printf("tm_mday:  %d\n",timeresult2.tm_mday);
          printf("tm_year:  %d\n",timeresult2.tm_year);
          printf("tm_yday:  %d\n",timeresult2.tm_yday);
          printf("tm_wday:  %d\n",timeresult2.tm_wday);
   }

        printf("Time Result 1 ===>minit: %d\n",timeresult1.tm_min);
        printf("Time Result 2 ===>minit: %d\n",timeresult2.tm_min);
	printf("Differnet =======>minit: %d\n",(timeresult2.tm_min-timeresult1.tm_min));

	if (!(timeresult2.tm_min-timeresult1.tm_min)){
		sleep(60);
		printf("will execute after one minute1\n");
	}
	else
		printf("after one minutes\n");


	/* free the result set */
 	mysql_free_result(result);

	/* close the connection */
	 mysql_close(connection);
 	printf("Done.\n");

	return 0;
}



