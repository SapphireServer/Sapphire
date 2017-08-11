#!/bin/bash
cd sql
mysql -u root -e 'create database sapphire;'
for f in *.sql
  do
    [ "$f" = "update.sql" ] && continue;
    echo -n "importing $f into the database..."
    mysql sapphire -u root < $f && echo "Success"
    CODE=$?
    if [ $CODE -ne 0 ]; then exit $CODE; fi
done
#mysql sapphire -u root < update.sql -f
echo 'todo: test update sql'
cd ..
