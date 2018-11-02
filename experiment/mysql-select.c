#include <stdio.h>
#include <mysql.h>
  
int main(char **args) {
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *connection, mysql;
	int state;
  
	/* connect to the MySQL database at localhost */
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,"localhost", "root", "toor", "rawdb", 0, 0, 0);

	/* check for a connection error */
	if (connection == NULL) {
		/* print the error message */
		printf(mysql_error(&mysql));
		return 1;
	}

	state = mysql_query(connection,"SELECT id, reg_date, firstkey FROM j1 ORDER BY reg_date DESC LIMIT 3");
	if (state != 0) {
		printf(mysql_error(connection));
		return 1;
	}

	/* must call mysql_store_result( ) before you can issue any other query calls */
    	result = mysql_store_result(connection);
    	printf("Rows: %d\n", mysql_num_rows(result));
    	/* process each row in the result set */
    	while ( ( row = mysql_fetch_row(result)) != NULL ) {
        	printf("id: %s, date:%s, key: %s\n",
            	(row[0] ? row[0] : "NULL"),
            	(row[1] ? row[1] : "NULL"),
		(row[2] ? row[2] : "NULL"));
 	}

	/* free the result set */
 	mysql_free_result(result);

	/* close the connection */
	 mysql_close(connection);
 	printf("Done.\n");

	return 0;
}
