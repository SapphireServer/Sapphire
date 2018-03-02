#ifndef CORE_FRAMEWORK_H
#define CORE_FRAMEWORK_H

#include <boost/shared_ptr.hpp>
#include <map>

#include "Forwards.h"


#include "ServerZone.h"

#include <common/Logging/Logger.h>

#include <common/Exd/ExdDataGenerated.h>

#include "Script/ScriptMgr.h"

#include "Linkshell/LinkshellMgr.h"

#include "Zone/TerritoryMgr.h"

#include "DebugCommand/DebugCommandHandler.h"

#include <common/Database/CharaDbConnection.h>
#include <common/Database/DbWorkerPool.h>

namespace Core
{

class Framework
{
private:

   Core::Logger g_log;
   Core::DebugCommandHandler g_debugCmdHandler;
   Core::Scripting::ScriptMgr g_scriptMgr;
   Core::Data::ExdDataGenerated g_exdDataGen;
   Core::TerritoryMgr g_territoryMgr;
   Core::LinkshellMgr g_linkshellMgr;
   Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;

public:

   Core::Logger& getLogger();
   Core::DebugCommandHandler& getDebugCommandHandler();
   Core::Scripting::ScriptMgr& getScriptMgr();
   Core::Data::ExdDataGenerated& getExdDataGen();
   Core::TerritoryMgr& getTerritoryMgr();
   Core::LinkshellMgr& getLinkshellMgr();
   Core::Db::DbWorkerPool< Core::Db::CharaDbConnection >& getCharaDb();
   Core::ServerZone& Core::Framework::getServerZone();

};

}
#endif // CORE_FRAMEWORK_H
