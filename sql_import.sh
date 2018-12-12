#!/bin/bash
cd bin
sapphire_dbm --mode initialize --user root --database sapphire --sfile sql/schema/schema.sql --ifile sql/schema/inserts.sql
sapphire_dbm --mode liquidate --user root --database sapphire --force
cd ..
