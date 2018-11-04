#!/bin/sh
rm 00*
echo 'hostname='$HOST
hostname -s > /tmp/0011-h
H=`cat /tmp/0011-h`
echo "Host"
echo $H
cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1 > /tmp/0012-randstring
echo "First Key"
cat  /tmp/0012-randstring
NF=`cat /tmp/0012-randstring`
echo "Second Key"
NL=`md5 -q /tmp/0012-randstring`
echo $NL 
STR2=$'INSERT INTO '$H' (firstkey, lastkey, mypoint, reg_date) VALUES ("'$NF'", "'$NL'", 2000000000, NOW())'
echo "$STR2" > /tmp/0013-insertintotable.sql

