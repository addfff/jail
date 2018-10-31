#include <stdlib.h>
#include <stdio.h>

int main(){
	MYSQL *sqlhnd = mysql_init(NULL);
    	mysql_real_connect(sqlhnd, "localhost", "rawuser1", "rawuser123", "rawdb", , NULL, 0);

	return 0;
}
