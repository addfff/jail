#!/bin/sh
rm 00*
echo 'hostname='$HOST
hostname -s > 001-h
H=`cat 001-h`
DB=$'rawdb'
STR1=$'CREATE TABLE '$H' (
	id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	firstkey VARCHAR(10) NOT NULL,
	lastkey VARCHAR(32) NOT NULL,
	mypoint INT(1) NOT NULL,
	reg_date TIMESTAMP
);'
echo "$STR1" > 002-createtable.sql
mysql --user=rawuser1 --password=rawuser123 $DB < 002-createtable.sql
cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > 003-randstring
echo "First Key"
cat  003-randstring
F=`cat 003-randstring`
echo "Second Key"
md5 -q 003-randstring
L=`md5 -q 003-randstring` 
STR2=$'INSERT INTO '$H' (firstkey, lastkey, mypoint, reg_date)
	VALUES ("'$F'", "'$L'", 2000000000, NOW()
);'
echo "$STR2" > 004-insertintotable.sql
mysql --user=rawuser1 --password=rawuser123 $DB < 004-insertintotable.sql
echo "Remember First Key is Password"
echo $F
STR3=$'CREATE USER "'$H'"@"localhost" IDENTIFIED BY "'$F'";'
echo "$STR3" > 005-createuser.sql
mysql --user=root --password=toor $DB < 005-createuser.sql
STR4=$'GRANT INSERT ON '$DB'.'$H' TO "'$H'"@"localhost";'
echo "$STR4" > 006-grantuser.sql
STR5=$'GRANT UPDATE ON '$DB'.'$H' TO "'$H'"@"localhost";'
echo "$STR5" >> 006-grantuser.sql
mysql --user=root --password=toor < 006-grantuser.sql
cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > 007-randstring
NF=`cat 007-randstring`
NL=`md5 -q 007-randstring`
STR6=$'INSERT INTO '$H' (firstkey, lastkey, mypoint, reg_date)
        VALUES ("'$NF'", "'$NL'", 2000000000, NOW()
);'
echo "$STR6" > 008-insertintotable.sql
mysql --user=$H --password=$F $DB < 008-insertintotable.sql
