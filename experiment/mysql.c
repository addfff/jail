#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <time.h>

int main(char **args) {
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *connection, mysql;
	int state;

    time_t t;
    struct tm *timeptr, tresult;

/*    setlocale(LC_ALL,"/QSYS.LIB/EN_US.LOCALE"); */
    t = time(NULL);
    timeptr = localtime(&t);
  
/* connect to the MySQL database at localhost */
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "rawuser1", "rawuser123", "rawdb", 0 , 0, 0);

/* check for a connection error */
	if (connection == NULL) {

/* print the error message */
		printf(mysql_error(&mysql));
		return 1;
	}

	state = mysql_query(connection, "SELECT firstkey, lastkey, reg_date FROM j1");
	if (state != 0) {
		printf(mysql_error(connection));
		return 1;
	}

/* must call mysql_store_result( ) before you can issue any other query calls */
    	result = mysql_store_result(connection);
    	printf("Rows: %d\n", mysql_num_rows(result));
/* process each row in the result set */
	while ( ( row = mysql_fetch_row(result)) != NULL ) {
        	printf("key1: %s, key2: %s, timestamp:%s\n", (row[0] ? row[0] : "NULL"), (row[1] ? row[1] : "NULL"), (row[2] ? row[2] : "NULL"));
 	}

    strftime(row[2],sizeof(row[2]), "%Y-%m-%d %r", timeptr);

    if (strptime(row[2], "%Y-%m-%d %r",&tresult) == NULL)
          printf("\nstrptime failed\n");
    else
    {
          printf("tm_hour:  %d\n",tresult.tm_hour);
          printf("tm_min:  %d\n",tresult.tm_min);
          printf("tm_sec:  %d\n",tresult.tm_sec);
          printf("tm_mon:  %d\n",tresult.tm_mon);
          printf("tm_mday:  %d\n",tresult.tm_mday);
          printf("tm_year:  %d\n",tresult.tm_year);
          printf("tm_yday:  %d\n",tresult.tm_yday);
          printf("tm_wday:  %d\n",tresult.tm_wday);
    }

 /* free the result set */
 	mysql_free_result(result);
 /* close the connection */
 	mysql_close(connection);
 	printf("Done.\n");

	return 0;
}


