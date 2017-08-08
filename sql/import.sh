#!/bin/bash
IMPORT_PATH="C://coding//repositories//ffxiv related//sapphire//Sapphire2Clone//sql//"
USER=root
PASS=root
DBNAME=sapphire

ECHO Creating Database $DBNAME
mysqladmin -h localhost -u $USER -p$PASS DROP $DBNAME

ECHO Creating Database $DBNAME
mysqladmin -h localhost -u $USER -p$PASS CREATE $DBNAME IF NOT EXISTS $DBNAME

ECHO Loading $DBNAME tables into the database
sh cd $IMPORT_PATH

"C:\program files\mysql\mysql server 5.7\bin\mysql" $DBNAME -h localhost -u $USER -p$PASS -e 'SET AUTOCOMMIT=0;'

for X in '*.sql';
do
	for Y in $X
	do
		echo Importing $Y;
		"C:\program files\mysql\mysql server 5.7\bin\mysql" $DBNAME -h localhost -u $USER -p$PASS < $Y
	done
done

"C:\program files\mysql\mysql server 5.7\bin\mysql" $DBNAME -h localhost -u $USER -p$PASS -e 'COMMIT;'

ECHO Finished!