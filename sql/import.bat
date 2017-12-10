@ECHO OFF
SETLOCAL
REM =============
REM IMPORT CONFIG
REM =============
REM NOTE: No spaces before or after the '='!!!

REM =============
SET PATH_MYSQL="Path\to\mysql.exe"
SET PATH_MYSQLADMIN="Path\to\mysqladmin.exe"
SET PATH_SQL="Path\to\Sapphire\sql"

SET USER=root
SET PASSWORD=
SET DBADDRESS=localhost
SET DBPORT=3306
SET DBNAME=sapphire
REM =============

IF DEFINED PASSWORD (SET PASSWORD=-p%PASSWORD%)

ECHO Deleteing old database
%PATH_MYSQLADMIN% -h %DBADDRESS% -u %USER% %PASSWORD% DROP %DBNAME%

ECHO Creating new database
%PATH_MYSQLADMIN% -h %DBADDRESS% -u %USER% %PASSWORD% CREATE %DBNAME%

ECHO Loading tables into the database
cd %PATH_SQL%
FOR %%X IN (*.sql) DO (
	IF "%%X"=="update.sql" (
		REM handle update.sql last
	) ELSE (
		ECHO Importing %%X
		%PATH_MYSQL% %DBNAME% -h %DBADDRESS% -u %USER% %PASSWORD% < %%X
	)
)

IF EXIST "update.sql" (
	ECHO Importing update.sql
	%PATH_MYSQL% %DBNAME% -h %DBADDRESS% -u %USER% %PASSWORD% < update.sql
)

ECHO Finished!

ENDLOCAL
PAUSE
@ECHO ON
