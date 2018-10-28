#!/bin/sh
rm 00*
echo 'hostname='$HOST
hostname -s > 0011-h
H=`cat 0011-h`
echo "Host"
echo $H
cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > 0012-randstring
echo "First Key"
cat  0012-randstring
NF=`cat 0012-randstring`
echo "Second Key"
NL=`md5 -q 0012-randstring`
echo $NL 
STR2=$'INSERT INTO '$H' (firstkey, lastkey, mypoint, reg_date)
	VALUES ("'$NF'", "'$NL'", 2000000000, NOW()
);'
echo "$STR2" > 0013-insertintotable.sql

