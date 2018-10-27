#!/bin/sh
echo 'hostname='$HOST
hostname -s > 001-h
H=`cat 001-h`
STR1=$'CREATE TABLE '$H' (
	id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	firstkey VARCHAR(10) NOT NULL,
	lastkey VARCHAR(32) NOT NULL,
	mypoint INT(1) NOT NULL,
	reg_date TIMESTAMP
)'
echo "$STR1" > 002-createtable.sql
mysql --user=rawuser1 --password=rawuser123 rawdb < 002-createtable.sql
cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > 003-randstring
echo "First Key"
cat  003-randstring
F=`cat 003-randstring`
echo "Second Key"
md5 -q 003-randstring
L=`md5 -q 003-randstring` 
STR2=$'INSERT INTO '$H' (firstkey, lastkey, mypoint, reg_date)
	VALUES ("'$F'", "'$L'", 2000000000, NOW()
)'
echo "$STR2" > 004-insertintotable.sql
mysql --user=rawuser1 --password=rawuser123 rawdb < 004-insertintotable.sql
