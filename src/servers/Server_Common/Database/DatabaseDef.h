#ifndef _DATABASEDEF_H
#define _DATABASEDEF_H

#include "src/libraries/sapphire/mysqlConnector/MySqlConnector.h"
#include <Server_Common/Database/DbLoader.h>
#include <Server_Common/Database/CharaDbConnection.h>
#include <Server_Common/Database/DbWorkerPool.h>
#include <Server_Common/Database/PreparedStatement.h>

extern Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;

#endif
