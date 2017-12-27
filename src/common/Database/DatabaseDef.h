#ifndef _DATABASEDEF_H
#define _DATABASEDEF_H

#include "src/libraries/sapphire/mysqlConnector/MySqlConnector.h"
#include <common/Database/DbLoader.h>
#include <common/Database/CharaDbConnection.h>
#include <common/Database/DbWorkerPool.h>
#include <common/Database/PreparedStatement.h>

extern Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;

#endif
