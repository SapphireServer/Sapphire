#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "ZoneMgr.h"
#include <Server_Common/Logger.h>
#include <Server_Common/Database.h>
#include "ServerZone.h"
#include "ScriptManager.h"
#include <Server_Common/ExdData.h>

extern Core::Logger g_log;
extern Core::Db::Database g_database;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Scripting::ScriptManager g_scriptMgr;
extern Core::Data::ExdData g_exdData;

#endif