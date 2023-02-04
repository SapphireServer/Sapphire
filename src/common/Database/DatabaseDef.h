#pragma once

#include <MySqlConnector.h>
#include "Database/DbLoader.h"
#include "Database/ZoneDbConnection.h"
#include "Database/DbWorkerPool.h"
#include "Database/PreparedStatement.h"

extern Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;

