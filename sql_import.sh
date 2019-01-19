#!/bin/bash
cd bin
./dbm --mode initialize --user root --database sapphire --sfile sql/schema/schema.sql --ifile sql/schema/inserts.sql
./dbm --mode liquidate --user root --database sapphire --force
cd ..
