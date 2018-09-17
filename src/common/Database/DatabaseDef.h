#ifndef _DATABASEDEF_H
#define _DATABASEDEF_H

#include <MySqlConnector.h>
#include "Database/DbLoader.h"
#include "Database/ZoneDbConnection.h"
#include "Database/DbWorkerPool.h"
#include "Database/PreparedStatement.h"

extern Core::Db::DbWorkerPool< Core::Db::ZoneDbConnection > g_charaDb;

#endif
