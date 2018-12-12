#!/bin/bash
bin/sapphire_dbm --mode initialize --user root --database sapphire --sfile bin/sql/schema/schema.sql --ifile bin/sql/schema/inserts.sql
bin/sapphire_dbm --mode liquidate --user root --database sapphire 
