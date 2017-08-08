#!/bin/bash
EXPORT_PATH="C://coding//repositories//ffxiv related//sapphire//Sapphire2Clone//sql//"
USER=root
PASS=root
DBNAME=sapphire
#test -d EXPORT_PATH || mkdir -p $EXPORT_PATH
list=`mysqlshow -u $USER -p$PASS $DBNAME`
for T in $list;
do
    if [[ "$T" != "information_schema" ]] && [[ "$T" != "performance_schema" ]] &&
     [[ "$T" != "mysql" ]] && [[ "$T" != "${DBNAME}"* ]] && [[ "$T" != *"*"* ]] && [[ "$T" != *"+"* ]] && [[ "$T" != *"+="* ]] &&
     [[ "$T" != "Tables" ]] && [[ "$T" != "Database"* ]] && [[ "$T" != "" ]]; then
        echo "Backing up " $T;
        mysqldump -u $USER -p$PASS $DBNAME $T --extended-insert=FALSE > "${EXPORT_PATH}/${T}.sql"
    fi
done;